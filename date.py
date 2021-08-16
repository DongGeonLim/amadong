
t = int(input())
d = t//86400
h = (t%86400)//3600
m = (t%3600)//60
s = t % 60
print(h)
print(m)


print(d, "day", "%02d:%02d:%02d" % (int(h),int(m),s))
