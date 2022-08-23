#!/usr/bin/env python
# coding: utf-8

# In[1]:


import cv2
import math
import numpy as np
import matplotlib.pyplot as plt


# In[2]:


im=cv2.imread("Downloads/test1.png")
img=np.copy(im)
g_img=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
ret,th_img=cv2.threshold(g_img,225,255,cv2.THRESH_BINARY)
plt.imshow(th_img,"gray");


# In[3]:


contours, hierarchy = cv2.findContours(th_img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)


# In[4]:


rl=np.array([0,0,50])
rh=np.array([50,50,255])
bl=np.array([0,50,0])
bh=np.array([50,255,50])
gl=np.array([50,0,0])
gh=np.array([255,50,50])
for contour in contours[1:]:
        
        cv2.drawContours(img, [contour], 0, (255, 255, 255), 5)
        approx = cv2.approxPolyDP(contour, 0.01 * cv2.arcLength(contour, True), True)
        c = cv2.moments(contour)
        if c['m00'] != 0.0:
            cx = int(c['m10']/c['m00'])
            cy = int(c['m01']/c['m00'])
         #COLORS
        if (img[cy,cx,0] >= 100 and img[cy,cx,0] <= 255) and (img[cy,cx,1] >= 0 and img[cy,cx,1] <=100) and (img[cy,cx,2] >= 0 and img[cy,cx,2] <=100):
                cv2.putText(img, "Blue", (cx-50,cy-50),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)
                
        elif (img[cy,cx,0] >= 0 and img[cy,cx,0] <= 100) and (img[cy,cx,1] >= 100 and img[cy,cx,1] <= 255) and (img[cy,cx,2] >= 0 and img[cy,cx,2] <= 100):
                cv2.putText(img, "Green", (cx-50,cy-50),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)
                
        elif (img[cy,cx,0] >= 0 and img[cy,cx,0] <=100) and (img[cy,cx,1] >= 0 and img[cy,cx,1] <= 100) and (img[cy,cx,2] >= 100 and img[cy,cx,2] <= 255):
                cv2.putText(img, "Red", (cx-50,cy-50),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2) 
        
        elif (img[cy,cx,0] >= 0 and img[cy,cx,0] <= 150) and (img[cy,cx,1] >= 150 and img[cy,cx,1] <= 255) and (img[cy,cx,2] >= 150 and img[cy,cx,2] <= 255):
                cv2.putText(img, "yellow", (cx-50,cy-50),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)        
        #shapes    
        if len(approx) == 3:
            cv2.putText(img, 'Triangle', (cx-50,cy),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)
        elif len(approx) == 4:
            x,y,w,h = cv2.boundingRect(approx)
            aspectRatio = float(w)/h
            if aspectRatio >= 0.9 and aspectRatio <=1.1:
                cv2.putText(img, "Square", (cx-50,cy),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2) 
            else:
                cv2.putText(img, "Rectangle", (cx-50,cy),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)
        elif len(approx) > 8:
            cv2.putText(img, 'circle', (cx-50,cy),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)
                    
plt.figure(figsize=(10,10))
img_rgb=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
plt.imshow(img_rgb)        


# In[5]:


# track direction 
l=np.array([0,0,0])
u=np.array([50,50,50])
track = cv2.inRange(im,l , u)
#plt.imshow(track,"gray");
sobel_y=np.array([[-1, -2, -1],
                  [ 0,  0,  0],
                  [ 1,  2,  1]])
htrack = cv2.filter2D(track,-1,sobel_y)
middle=(htrack.shape[0])/2
if htrack[:,int(middle):].sum()+100<htrack[:,0:int(middle)].sum() :
    text="to left"
elif htrack[:,0:int(middle)].sum()+100<htrack[:,int(middle):].sum() :
    text="to right"
else:
    text="neither nor"
cv2.putText(img, text, (int(middle)+100,70),cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2) 
plt.figure(figsize=(10,10))
img_rgb=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
plt.imshow(img_rgb) ;


# In[ ]:




