import pickle
import os
import datetime
import math
import random

review_list = []
review_event = []
discount = []
user_input_list = ["Restaurant Name:", "Name:", "Review:", "Star Score:"]

REVIEW_RETRIEVE = 1
REVIEW_ADD = 2
REVIEW_UPDATE = 3
REVIEW_DELETE = 4
RECOMMENDER_NAME = 5
DISCOUNT = 6
EVENT_RESULT = 7
REVIEW_SAVE = 8
REVIEW_LOAD = 9
QUIT = 10

def print_menu():
    print("**************************")
    print("1. Review Retrieve")
    print("2. Review Add")
    print("3. Review Update")
    print("4. Review Delete")
    print("5. Recommender Name")
    print("6. Discount")
    print("7. Event Result")
    print("8. Review Save")
    print("9. Review Load")
    print("10. Quit")
    print("**************************")

def print_list():
    print("INDEX    RESTAURANT NAME        YOUR NAME        STAR SCORE        TIME")
    print("*************************************************************************************")
    for j in range(len(review_list)):
        print((str(j+1)+".").ljust(5), " ", str(review_list[j][0]).rjust(3), " ", str(review_list[j][1]).rjust(18), " ",  str(review_list[j][3]).rjust(12), " ", str(review_list[j][4]).rjust(15))
        print("Review:", str(review_list[j][2]))
    print("*************************************************************************************")
    print()

print_menu()

while True:
    try:
        input_num = int(input(">"))

    except ValueError as e:
        print("The input has errors.")
        continue

    if 1 <= input_num <= 10:
        if input_num == REVIEW_RETRIEVE:
            if not review_list:
                print("There are no data.")

            else:
                print_list()

        elif input_num == REVIEW_ADD:
                  
            if len(review_list) >= 9999:
                print("No more data is accepted.")
                continue

            else:
                add_list_temp = []              

                while True:
                    if len(add_list_temp) == 0:
                        restaurant_name = input(user_input_list[0])

                        if 1 <= len(restaurant_name) < 25:
                            add_list_temp.append(restaurant_name)

                        elif len(restaurant_name) == 0:
                            print("The input has errors.")
                            continue

                        else:
                            print("The length of restaurant name should be less than 25")
                            print("The input has errors.")
                            continue

                    if len(add_list_temp) == 1:
                        your_name = input(user_input_list[1])

                        if 1 <= len(your_name) < 20:
                            add_list_temp.append(your_name)

                        elif len(your_name) == 0:
                            print("The input has errors.")
                            continue

                        else:
                            print("The length of name should be less than 20")
                            print("The input has errors.")
                            continue

                    if len(add_list_temp) == 2:
                        review = input(user_input_list[2])

                        if 1 <= len(review) < 50:
                            add_list_temp.append(review)

                        elif len(review) == 0:
                            print("The input has errors.")
                            continue

                        else:
                            print("The length of review should be less than 50")
                            print("The input has errors.")
                            continue

                    if len(add_list_temp) == 3:
                        try:
                            score = float(input(user_input_list[3]))
                            star_score = math.ceil(score)

                        except ValueError as e:
                            print("The input has errors.")
                            continue
                            
                        if 0 < star_score <= 5:
                            add_list_temp.append(("☆" * star_score))

                        elif star_score > 5:
                            print("The maximum of star score is five points.")

                        else:
                            print("The input has errors.")
                            continue

                    if len(add_list_temp) == 4:
                        add_list_temp.append(datetime.datetime.now())
                        review_list.append(add_list_temp)
                        print("Added.")
                        break

        elif input_num == REVIEW_UPDATE:
            if not review_list:
                print("There are no data.")

            else:
                update_list_temp = []
                update_flag = True
                print_list()

                while True:
                    if update_flag:
                        try:
                            update_num = int(input("Update>"))

                        except ValueError as e:
                            print("The input has errors.")
                            continue

                    if 1 <= update_num <= len(review_list):

                        if len(update_list_temp) == 0:
                            restaurant_name = input(user_input_list[0])

                            if 1 <= len(restaurant_name) < 25:
                                update_list_temp.append(restaurant_name)

                            elif len(restaurant_name) == 0:
                                print("The input has errors.")
                                update_flag = False
                                continue

                            else:
                                print("The length of restaurant name should be less than 25")
                                print("The input has errors.")
                                update_flag = False
                                continue

                        if len(update_list_temp) == 1:
                            your_name = input(user_input_list[1])

                            if 1 <= len(your_name) < 20:
                                update_list_temp.append(your_name)

                            elif len(your_name) == 0:
                                print("The input has errors.")
                                update_flag = False
                                continue

                            else:
                                print("The length of name should be less than 20")
                                print("The input has errors.")
                                update_flag = False
                                continue

                        if len(update_list_temp) == 2:
                            review = input(user_input_list[2])

                            if 1 <= len(review) < 50:
                                update_list_temp.append(review)

                            elif len(review) == 0:
                                print("The input has errors.")
                                update_flag = False
                                continue

                            else:
                                print("The length of review should be less than 50")
                                print("The input has errors.")
                                update_flag = False
                                continue

                        if len(update_list_temp) == 3:
                            try:
                                score = float(input(user_input_list[3]))
                                star_score = math.ceil(score)

                            except ValueError as e:
                                print("The input has errors.")
                                update_flag = False
                                continue
                            
                            if 0 < star_score <= 5:
                                update_list_temp.append(("☆" * star_score))

                            elif star_score > 5:
                                print("The maximum of star score is five points.")
                                update_flag = False

                            else:
                                print("The input has errors.")
                                update_flag = False
                                continue

                        if len(update_list_temp) == 4:
                            update_list_temp.append(datetime.datetime.now())
                            review_list[update_num-1] = update_list_temp
                            print("Updated.")
                            break
                    else:
                        print("The input has errors.")
                        continue

        elif input_num == REVIEW_DELETE:
            if not review_list:
                print("There are no data.")

            else:
                print_list()

                while True:
                    try:
                        delete_num = int(input("Delete>"))

                        if 1 <= delete_num <= len(review_list):
                            del review_list[delete_num-1]
                            print("Deleted.")
                            break

                        else:
                            print("The input has errors.")

                    except ValueError as e:
                        print("The input has errors.")
                        continue

        elif input_num == RECOMMENDER_NAME:
            reviewer_name_list = []
            restaurant_name_flag = False

            if not review_list:
                print("There are no data.")

            else:
                print_list()
                reviewer_name = input("Recommender Name: ")

                if 1 <= len(reviewer_name) < 20:
                    for i in range(len(review_list)):
                        if reviewer_name == str(review_list[i][1]):
                            reviewer_name_list.append(review_list[i])

                    if len(reviewer_name_list) == 0:
                        print("Name not found.")

                    else:
                        restaurant_name_check = input("Restaurant Name: ")
                        for i in range(len(reviewer_name_list)):
                            if restaurant_name_check == str(reviewer_name_list[i][0]):
                                restaurant_name_flag = True

                        if restaurant_name_flag:
                            event_name = input("Your Name: ")
                            if event_name not in review_event:
                                review_event.append(event_name)
                                discount.append(reviewer_name)
                                print("Your name is now on the event list.")

                            else:
                                print("You are already in the event list.")

                        else:
                            print("Restaurant not found.")

                else:
                    print("The length of recommender name should be less than 20")
                    continue

        elif input_num == DISCOUNT:
            if not review_list:
                print("There are no data.")

            else:
                print_list()
                discount_name = input("Your Name: ")
                discount_rate = discount.count(discount_name)

                if discount_rate == 0:
                    print("Name not found.")
                    
                else:
                    if discount_rate >= 20:
                        print("Congratulations! Maximum discount! (20%)")
                    else:
                        print("Congratulations! ", discount_rate, "%", " discount!", sep='')
       
        elif input_num == EVENT_RESULT:
            if not review_list:
                print("There are no data.")

            else:
                print("You can be a winner on this event with a probability of 25% :D")
                your_name = input("Your Name: ")

                if your_name in review_event:
                    num_a = random.sample(range(1,5), 1)
                    num_b = random.sample(range(1,5), 1)

                    if num_a == num_b:
                        print("Congratulations! You have won an event!")
                    else:
                        print("Sorry. Try again next time!")

                    review_event.remove(your_name)

                else:
                    print("Your name is not on the event list. Try '5(Recommender_Name)' first.")

        elif input_num == REVIEW_SAVE:
            if not review_list:
                print("There are no data.")

            else:
                print_list()
                save_list = review_list
                file = open('DATA.dat', 'wb')
                pickle.dump(save_list, file)
                file.close
                print("Saved.")

        elif input_num == REVIEW_LOAD:
            if not os.path.isfile('DATA.dat'):
                print("There is no files.")

            else:
                file = open('DATA.dat', 'rb')
                save_list = pickle.load(file)
                file.close()
                print("Loaded.")

        elif input_num == QUIT:
            print("Bye Bye!!")
            break

    else:
        print("The input has errors.")
        continue

    print()
    print_menu()
