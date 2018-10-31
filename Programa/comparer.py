import matplotlib.image as img
import sys

if len(sys.argv) != 4:
    print("modo de uso: python3.5 comparer.py image1.png image2.png imageout.png")

else:
    path1 = sys.argv[1]
    path2 = sys.argv[2]
    path3 = sys.argv[3]
    image1 = img.imread(path1)
    image2 = img.imread(path2)
    image3 = img.imread(path1)



    dif_pixels = 0
    diference = 0
    for i in range(len(image1)):
        for j in range(len(image1[i])):
            diffR = abs(image1[i][j][0] - image2[i][j][0])
            diffG = abs(image1[i][j][1] - image2[i][j][1])
            diffB = abs(image1[i][j][2] - image2[i][j][2])
            total_diff = diffB + diffG + diffR
            if total_diff > 0.005:
                dif_pixels += 1
                print(i,j,diffR,diffG,diffB)
            image3[i][j][0] = diffR
            image3[i][j][1] = diffG
            image3[i][j][2] = diffB
    print("procentaje de pixeles distintos:", dif_pixels * 100 / (len(image1)*len(image1[0])))
    print("pixeles distintos:", dif_pixels)
    img.imsave(path3, image3)
