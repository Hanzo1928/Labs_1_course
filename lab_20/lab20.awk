#!/usr/bin/bash awk

{
    if ($1 == "cos") {
	   print "---------------------------------------"
	   print "|  F(x):  |  Arguments:  |  Results:  |"
	   print "---------------------------------------"
	   i = 2
	   while (i <= NF) {
		     x=$i
		     y=cos($i)
		     printf "|   cos   |   %f   |  %f  |\n",x,y
		     i += 1
		 }
		 printf "---------------------------------------\n\n\n"

       }
       if ($1 == "sin") {
	   print "---------------------------------------"
	   print "|  F(x):  |  Arguments:  |  Results:  |"
	   print "---------------------------------------"
	   i = 2
	   while (i <= NF) {
		     x=$i
		     y=sin($i)
		     printf "|   sin   |   %f   |  %f  |\n",x,y
		     i += 1
		 }
		 printf "---------------------------------------\n\n\n"

       } if ($1 == "exp") {
	   print "---------------------------------------"
	   print "|  F(x):  |  Arguments:  |  Results:  |"
	   print "---------------------------------------"
	   i = 2
	   while (i <= NF) {
		     x=$i
		     y=exp($i)
		     printf "|   exp   |   %f   |  %f  |\n",x,y
		     i += 1
		 }
		 printf "---------------------------------------\n\n\n"

       }   if ($1 == "log") {
	   print "---------------------------------------"
	   print "|  F(x):  |  Arguments:  |  Results:  |"
	   print "---------------------------------------"
	   i = 2
	   while (i <= NF) {
		     x=$i
		     y=log($i)
		     printf "|   log   |   %f   |  %f  |\n",x,y
		     i += 1
		 }
		 printf "---------------------------------------\n\n\n"

       }   if ($1 == "sqrt") {
	   print "---------------------------------------"
	   print "|  F(x):  |  Arguments:  |  Results:  |"
	   print "---------------------------------------"
	   i = 2
	   while (i <= NF) {
		     x=$i
		     y=sqrt($i)
		     printf "|   sqrt   |   %f   |  %f  |\n",x,y
		     i += 1
		 }
		 printf "---------------------------------------\n\n\n"

       }
}
