#Project: project1
#Miller, Keegan
#671603821
#https://replit.com/@Kmill34/Project1#main.py

import turtle
from random import randint
from turtle import Screen
import datetime
import pytz

tz = pytz.timezone("America/Chicago")
#aware = tz.localize(datetime(2011, 2, 11, 20), is_dst=None)
screen = Screen()
WIDTH,HEIGHT = 500, 500
screen.setup(WIDTH, HEIGHT)

t1=turtle
t1.speed(200)
t2=turtle
t2.speed(200)

#This is my list
Colors = ["Red","Purple","Pink","Orange","Green","Cyan","Brown","Gray","Maroon","Gold","Turquoise","Teal"]

#This Function creates Rectangles
def draw_rectangle(t,x,y,header,pensize,pencolor,fillcolor,length,width):
  t.hideturtle()
  t.penup()
  t.goto(x, y)
  t.pendown()
  t.pensize(pensize)
  t.pencolor(pencolor)
  t.setheading(header)
  t.begin_fill()
  t.fillcolor(fillcolor)
  
  for i in range(2):
    t.forward(width)
    t.left(90)
    t.forward(length)
    t.left(90)
  t.end_fill()

#This function creates my isoselesce triangle
def draw_triangle(t,x,y,header,pensize,pencolor,fillcolor,side_length,big_side):
  t.hideturtle()
  t.penup()
  t.goto(x,y)
  t.pendown()
  t.pensize(pensize)
  t.pencolor(pencolor)
  t.setheading(header)
  t.begin_fill()
  t.fillcolor(fillcolor)
  for j in range(1):
    t.forward(side_length)
    t.left(20)
    t.forward(big_side)
    t.left(170)
    t.forward(big_side)
    t.left(20)
  t.end_fill()

#This functions creates my circle
def draw_circle(t,x,y,header,pensize,pencolor,fillcolor,extent,radius,steps=None):
  t.penup()
  t.goto(x,y)
  t.pendown()
  t.pensize(pensize)
  t.pencolor(pencolor)
  t.setheading(header)
  t.hideturtle()
  t.begin_fill()
  t.fillcolor(fillcolor)
  
  for k in range(1):
    t.circle(radius,extent)
  t.end_fill()

#This is my draw shape function which makes a star
def draw_shape(t,x,y,header,pensize,pencolor,fillcolor,length):
  t.penup()
  t.goto(x,y)
  t.pendown()
  t.pensize(pensize)
  t.pencolor(pencolor)
  t.setheading(header)
  t.begin_fill()
  t.fillcolor(fillcolor)
  for i in range(5):
    t.forward(length)
    t.left(144)
  t.end_fill()

#This is my draw oval function used for my spaceship
def draw_oval(t,x,y,header,pensize,pencolor,fillcolor,r,extent):
  t.penup()
  t.goto(x,y)
  t.pendown()
  t.pensize(pensize)
  t.pencolor(pencolor)
  t.setheading(header)
  t.begin_fill()
  t.fillcolor(fillcolor)
  for i in range(2):
    t.circle(r,90)
    t.circle(r//64,90)
    #t.circle(r,extent)
  t.end_fill()
#def draw_window():
  #for i in range(20):

#This is my draw object function which calls rectangle, cirlce, and triangle 
def draw_object(x,y,length,width,Antenna):
  draw_rectangle(t1,x,y,0,1,"black",Colors[randint(0,11)],length,width)
  #for i in range(2):
  draw_rectangle(t1,x+10,y+50,0,1,"yellow","yellow",10,5)
  draw_rectangle(t2,x+5,y+20,0,1,"yellow","yellow",10,5)
  draw_rectangle(t2,x+15,y+20,0,1,"yellow","yellow",10,5)
  draw_rectangle(t1,x+5,y+80,0,1,"yellow","yellow",10,5)
  #draw_rectangle
  draw_triangle(t2,x+width,y+length,80,1,"White","white",1,Antenna)
  draw_triangle(t2,x+3,y+length,80,1,"White","white",1,Antenna)
  draw_circle(t1,x,y+length+Antenna,0,1,"red","red",360,2)
  draw_circle(t2,x+width-3,y+length+Antenna,0,1,"red","red",360,2)

#This function creates a planetarium
def draw_planetarium():
  draw_rectangle(t1,-290,-148,0,1,"black","gray",20,100)
  draw_rectangle(t1,-278,-128,0,1,"black","gray",7,75)
  draw_circle(t1,-210,-121,90,1,"black","gray",180,30)

#This function creates a spaceship using cirlce and oval and rectangle
def draw_spaceship():
  draw_circle(t1,0,-10,45,1,"green","green",180,40)
  draw_oval(t2,-90,55,270,1,"gray","gray",100,2)
  draw_rectangle(t1,5,-18,45,1,"gray","gray",100,10)

#This is my background function which contains a for loop for the stars along with a random number generator and an if statement which switches the background from day to night depending on the day
def draw_background():
  now = datetime.datetime.now(tz)
  draw_circle(t2,-270,100,0,1,"yellow","yellow",360,20)
  if now.hour < 6 and now.minute >= 0:
    t1.bgcolor("black")
    draw_spaceship()
    #t1.goto(randint(-100,0),randint(0,100))
    for i in range(100):
      draw_shape(t2,randint(-300,300),randint(0,200),2,1,"yellow","yellow",5)
  if now.hour > 6 and now.hour < 20 and now.minute >= 0:
    t1.bgcolor("blue")
    style=("Courier",20)
    t1.penup()
    t1.goto(-100,0)
    t1.pendown()
    t1.write("ALIENS ARE COMING!!!!",align="left",font=style)
  if now.hour > 20 and now.minute >= 0:
    t1.bgcolor("black")
    draw_spaceship()
    #t1.goto(randint(-100,0),randint(0,100))
    for i in range(100):
      draw_shape(t2,randint(-300,300),randint(0,200),2,1,"yellow","yellow",5)

#Here is the main function which calls the whole project together
def main():
  t1.tracer(0,0)
  t2.tracer(0,0)
  draw_planetarium()
  draw_background()
  draw_object(-160,-150,100,30,20)
  draw_object(-110,-150,100,50,20)
  draw_object(-50,-150,100,40,20)
  draw_object(0,-150,100,45,20)
  draw_object(80,-150,100,20,20)
  draw_object(120,-150,100,35,20)
  draw_object(180,-150,100,25,20)
  draw_object(220,-150,100,23,20)
  draw_object(255,-150,100,38,20)
  t1.update
  t2.update()

main()
print("Keegan Miller 671603821")

#draw_object(-180,-100,100,20)

#draw_triangle(t3,-170,-40,80,1,"red","red",1,40)
#draw_spaceship()

#The for loop is on line: 
#148

#The random number generator is on line: 
#149

#The Conditional Statement is on Line:
#144

#The list is created on line 24





