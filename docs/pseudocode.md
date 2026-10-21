# Gate processing pseudocode

~~~text
READ nonnegative starting balance
CREATE SmartCard with balance
READ journey count
FOR each journey
    READ zone, retrying after nonnumeric input or out-of-range time
    READ hour and minute
    READ fare mode and passenger kind
    VALIDATE zone
    CALCULATE fare quote from zone, time, passenger, and mode
    IF monthly pass OR balance - fare >= minimum balance
        APPROVE journey
        DEDUCT fare only for stored-value card
    ELSE
        DENY journey and preserve balance
    PRINT fare, decision, and remaining balance
END FOR
~~~
