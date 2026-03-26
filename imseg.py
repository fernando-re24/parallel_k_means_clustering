import sys # for command line arguments
from PIL import Image, ImageOps # for image processing
import numpy as np # for matrix processing
import ctypes as ct # for calling C from Python

# load C kmeans library
######################
kmeans_lib = ct.CDLL("./kmeans.so")
kmeans_lib.calc_kmeans.argtypes = [
    ct.POINTER(ct.c_double),  # data
    ct.c_int,                 # num_points
    ct.c_int,                 # dim
    ct.POINTER(ct.c_double),  # kmeans
    ct.c_int,                 # k
    ct.c_int                  # m
]
kmeans_lib.calc_kmeans.restype = None
######################

# read command line arguments
if (len(sys.argv) < 5):
    print ("Not enough command line arguments")
    exit(1)
infile = sys.argv[1]
outfile = sys.argv[2]
k = int(sys.argv[3])
m = int(sys.argv[4])

# read the input image file
image = Image.open(infile)
A = np.array(image,dtype='float64')
rows,cols,colors = A.shape

# create a kmeans matrix
kmeans = np.zeros((k,colors),dtype='float64')

# call the C kmeans function
######################
data = A.reshape(-1, colors)
num_points = data.shape[0]
dim = colors

kmeans_lib.calc_kmeans(
    data.ctypes.data_as(ct.POINTER(ct.c_double)),
    ct.c_int(num_points),
    ct.c_int(dim),
    kmeans.ctypes.data_as(ct.POINTER(ct.c_double)),
    ct.c_int(k),
    ct.c_int(m)
)
######################

# replace each color with the nearest mean color
dist_sq = np.zeros((rows,cols,k))
for i in range(k):
    dist_sq[:,:,i] = np.sum((A-kmeans[i])*(A-kmeans[i]),axis=2)
clusters = np.argmin(dist_sq,axis=2)
B = kmeans[clusters]

# output the resulting image
result = Image.fromarray(np.uint8(np.round(B)))
result.save (outfile)
