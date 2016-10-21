Compilation Instructions for part 1
Please use the following command:
gcc olmhash.c -o olmhash
To run:
./olmhash N
where N is the number of password limit attempts
Trying to run the program without an interger N value will cause it to crash

KNOWN ISSUES/BUGS:
Passwords that are less than 12 characters will not allow you to login once set.
This is due to the padding that is added.
