weight = input("please input your weight : ")
height = input("please input your height : ")

BMI = weight/(height*height)
	
if BMI < 18.5 :
	print 'slender'
elif 18.5 <= BMI and BMI < 25.0 :
	print 'regular'
elif 25.0 <= BMI and BMI < 30.0 :
	print 'obesity' 
elif 30.0 <= BMI :
	print 'dangerout'
