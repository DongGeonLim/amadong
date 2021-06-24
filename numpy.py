#numpy 13p
l = [[1,2,3],[4,5,6]]

for i,a in enumerate(l):
	for j,b in enumerate(a):
		print(l[i][j])

# 실행결과
'''
1
2
3
4
5
6
'''
#numpy 16p
hello = "lodybabo"

if hello.startswith("l"):
	print(True)

baby = "langE cat"

if baby.startswith("langE"):
	print(True)

ddong = "goodfood"

if ddong.startswith("go"):
	print("?")
else:
	print("!")

wow = "wow!"

if wow.startswith("!"):
	print("?")
else:
	print("no", "no", "!", end = '')
	print("no")
	print("no")

# 실행결과
'''
True
True
?
no no !no
no
'''

# import numpy as np

# # action = np.array([[-1.0],[0,1],[1,0],[0,-1]])

# # action

# a = [1,2,3,4]

# b = np.array(a)
