# Ajax-for-distance-measurement
Using Ultrasonic sensor to measure distance and using nodemcu to send distance onto to a webpage without refresh using ajax.
In this code we are going to send distance between an obstacle onto a webpage using nodemcu to send the data without a page refresh we will use ajax .
# Why to use AJAX?
In this project we are updating a varying value of distance so everytime the data is send to the webpage the webpage needs to be refreshed and we cannot expect the user to manually refresh the webpage so we instead use AJAX to update only a particular data on the webpage
# How does AJAX does this?
Now AJAX uses a object named as XMLHttpRequest object which is an object present in all the web browsers. This object has various methods in it which we can use.
In AJAX as you can see it is asynchronous javascript and xml so we use javascript to use the objects method and XML to store the data which we are sendding to webpage.
