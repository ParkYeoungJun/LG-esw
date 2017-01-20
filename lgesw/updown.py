import random

result = random.randint(1,100)

print 'Random int is 1 to 100\n' 

i = 0
yes = "Y"
no = "N"
dummy = 0

check = 0

while i < 7 :

	if i == 6 :
		print 'Fail !!\n'
		regame = raw_input('Regame?? [Y/N]') 

		if regame == yes :
			result = random.randint(1,100)
			i = 0
			dummy = raw_input()
		elif regame == no :
			print 'Thank you\n'
			break

	user = raw_input('Please input your value : ')	

	try:
		user = int(user)
	except ValueError:
		print 'Please input Integer\n'
		check = 1

	if user < 1 or user > 100 and check == 0 :
		print 'Please input 1 to 100\n'
	elif user >= 1 and user <= 100 and result > user : 
		print 'Higher than your value\n'
		i = i + 1
	elif user >= 1 and user <= 100 and result < user :
		print 'Lower than your value\n'
		i = i + 1
	elif user >= 1 and user <= 100 and result == user :
		print 'Congraturation\n' 
		i = 6
			
	check = 0
			

