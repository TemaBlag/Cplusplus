a = [i for i in input().split()]
n = 0
b = [] 
while( a[0] != "end"):
    b.append(a)
    n += 1
    a = [ i for i in input().split()] 
k = len(b[0])
for i in range(n):
    for j in range(k):
            s = [i-1,i+1,j-1,j+1]
            if( i == 0 ):
                s[0] = n - 1
            if (j == 0):
                s[3] == k - 1
            if (i == n - 1):
                s[1] == 0  
            if (j ==  k - 1):
                s[3] == 0  
            b[i][j] = int(b[s[0]][j]) + int(b[s[1]][j]) + int(b[i][s[2]]) + int(b[i][s[3]])              
for i in range(n):
    for j in range(k):
        print(b[i][j], end=" ")
    print()
