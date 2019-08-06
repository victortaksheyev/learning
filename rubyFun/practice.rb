# print "enter a value: "

# first_num = gets.to_i

# print "Enter another Value: "

# second_num = gets.to_i


# # print will not put a newline after the message puts will

# puts first_num.to_s + " + " + second_num.to_s + " = " + (first_num + second_num).to_s



# arithmetic operators 
# puts "6+4 = " + (6+4).to_s
# print "6-4 = " + (6-4).to_s


#data types
# num_one = 1.000
# num99 = 0.999 # there must always be a number before decimal for floats

# print num_one.to_s + "-" + num99.to_s + "=" + (num_one - num99).to_s

# every thing in ruby is an object
# puts 1.234.class #prints out the datatype (object type)

# A_CONSTANT = 3.14 #with uppercase

=begin
This is a multiline comment
=end 

=begin
age = 12
if (age >= 5) && (age <= 6)
  puts "kindergarden"
elsif (age >= 7) 
puts "ms"
else
  puts "home"
end

=end

=begin
# puts "ruby > python" if 5 < 10 
age = 12
print "Enter Greeting: " 
greeting = gets.chomp

case greeting
when "French", 'french'
  puts "Bonjour"
  exit
when "spanish", "Spanish"
  puts "hola"
  exit
else "English"
  puts "hi"
end
=end

# looping
x = 1
loop do
x+=1
puts x if (x % 2 == 0)
break if x == 100


end



