# PRJ_CarRental

I have made a console application that works with an http server using the httplib library.
I have used this library because is just a header file and portable.

Non dependencies required

To execute the program you can just compile it from Visual Studio Project so the UI will promt.

![image](https://github.com/user-attachments/assets/9dbfbbdf-4ee2-40ad-a84d-678877e784ac)

Here we get info from a "DB" that I populated in "CDatabase.cpp"

![image](https://github.com/user-attachments/assets/fdf27295-ba70-492b-a1c1-0d719c08f492)

The DB Info is the next one:
CUSTOMERS:
0 - Name: Alberto | Points: 0 | Rented Car:  | Invoice: 0
1 - Name: Kevin | Points: 0 | Rented Car:  | Invoice: 0
2 - Name: Ana | Points: 0 | Rented Car:  | Invoice: 0
3 - Name: Sanna | Points: 0 | Rented Car:  | Invoice: 0
4 - Name: Victor | Points: 0 | Rented Car:  | Invoice: 0
5 - Name: Maria | Points: 0 | Rented Car:  | Invoice: 0

CARS:
0 - Name: BMW 7 | Plate: LPN001 | Price: 300
1 - Name: Kia Sorento | Plate: LPN002 | Price: 150
2 - Name: Nissan Juke | Plate: LPN003 | Price: 150
3 - Name: Seat Ibiza | Plate: LPN004 | Price: 50

After selecting one index we will get the selection of 3 modes: Renting, Returning and Change User.

#RENTING:#
We have selected Ana as user, and we rent a Kia Sorento for 4 days.
![image](https://github.com/user-attachments/assets/796d7e32-14f8-4da1-a2d5-92b871236d07)

As we see ana now have to pay 600 for those 4 days.
![image](https://github.com/user-attachments/assets/101e6153-5615-4ed5-912b-c454a49e0fcf)

#RETURNING:#
Now we will return the car, but used for more than 4 days, in this case will be for 5 days.
The invoice amount should change to 600 + (150 + (150 * 0.6)) = 840
![image](https://github.com/user-attachments/assets/44bf326c-8d14-435a-a1a2-1923bd9480f9)



