# Watershed
Implementation of the waterhed segmentation in C

You can represent the results of the algorithm in grayscale, in color or or by highlighting the contour of the objects

It works with a picture and an image of markers associated with the picture


### Use
To compile, type in command line ``` gcc main.c -o watershed ```

To execute, type in command line :
- ```./watershed -grey avion``` (or another folder containig images) to obtain the results of the algorithm in grayscale or
- ```./watershed -color avion``` (or another folder containig images) to obtain the results of the algorithm with colors or
- ```./watershed -contour avion``` (or another folder containig images) to obtain the results of the algorithm highlighting the contour of objects 


### Example 
![lotus](https://user-images.githubusercontent.com/79161859/115968638-1d67e880-a539-11eb-8dda-121966673f3d.png)

![lotus_lpe_gris](https://user-images.githubusercontent.com/79161859/115968645-2658ba00-a539-11eb-8210-59984c19223e.png)

![lotus_lpe_couleurs](https://user-images.githubusercontent.com/79161859/115968652-2b1d6e00-a539-11eb-9ee2-095933fef57d.png)

![lotus_lpe_contour](https://user-images.githubusercontent.com/79161859/115968659-2f498b80-a539-11eb-99aa-dc22757c31db.png)
