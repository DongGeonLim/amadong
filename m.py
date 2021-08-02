import pyautogui
import pyperclip
import keyboard
import time

btn_first=pyautogui.prompt(title='안녕', text='너의 이름은?')

btn_next=pyautogui.prompt(title='안녕', text='너의 전화번호 가운데 4자리는?')
if (len(btn_next) != 4 or btn_next.isdigit() is False):
    while (len(btn_next) != 4 or btn_next.isdigit() is False):
        pyautogui.alert("정확하게 입력해주세요")
        btn_next=pyautogui.prompt(title='안녕', text='너의 전화번호 가운데 4자리는?')

btn_last=pyautogui.prompt(title='안녕', text='너의 전화번호 마지막 4자리는?')
if (len(btn_last) != 4 or btn_last.isdigit() is False):
    while (len(btn_last) != 4 or btn_last.isdigit() is False):
        pyautogui.alert("정확하게 입력해주세요")
        btn_last=pyautogui.prompt(title='안녕', text='너의 전화번호 마지막 4자리는?')

pyautogui.alert("1 : 클릭 \n2 : 스크롤 \n3 : 이름 입력 \n4,5 : 전화번호 입력 \nd : 실행")

list1 = []

while True:
    if keyboard.is_pressed('1'):
        q = pyautogui.position()
        print(q)
        time.sleep(0.2)
        list1.append(q)
    if keyboard.is_pressed('2'):
        w = 'scroll'
        print('scroll')
        time.sleep(0.2)
        list1.append(w)
    if keyboard.is_pressed('3'):
        e = 'name'
        print('name')
        time.sleep(0.2)
        list1.append(e)
    if keyboard.is_pressed('4'):
        r = 'num1'
        print('num1')
        time.sleep(0.2)
        list1.append(r)
    if keyboard.is_pressed('5'):
        t = 'num2'
        print('num2')
        time.sleep(0.2)
        list1.append(t)
    if keyboard.is_pressed('d'):
        print(len(list1))
        l = int(len(list1))
        break

for n in range(0, l):
    if list1[n] == str('scroll'):
        pyautogui.scroll(-1000)
    elif list1[n] == str('name'):
        pyperclip.copy(btn_first)
        pyautogui.hotkey('ctrl', 'v')
    elif list1[n] == str('num1'):
        pyperclip.copy(btn_next)
        pyautogui.hotkey('ctrl', 'v')
    elif list1[n] == str('num2'):
        pyperclip.copy(btn_last)
        pyautogui.hotkey('ctrl', 'v')
    else:
        pyautogui.click(list1[n], duration=0.3)
        

