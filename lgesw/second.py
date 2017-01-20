x = input("input second : ")

day, hour, mi, second = 0,0,0,0

oneday = 3600*24

day = x/oneday

x = x-(oneday*day)

hour = x/3600


x = x-(hour*3600)

mi = x/60

x = x-(mi*60)

second = x

print str(day) + ' day ' + str(hour) + ' hour '+ str(mi) + ' mi ' + str(second) + ' second\n' 
