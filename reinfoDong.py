import numpy as np
import copy
import math
from tqdm import tqdm


class Environment():
    
    def __init__(self):
    # 보드는 0으로 초기화된 25개의 배열로 준비
    # 게임종료 : done = True
        self.board_a = np.zeros(25)
        self.done = False
        self.reward = 0
        self.winner = 0
        self.print = False

    def move(self, p1, p2, player):
    # 각 플레이어가 선택한 행동을 표시 하고 게임 상태(진행 또는 종료)를 판단
    # p1 = 1, p2 = -1로 정의
    # 각 플레이어는 행동을 선택하는 select_action 메서드를 가짐
        if player == 1:
            pos = p1.select_action(env, player)
        else:
            pos = p2.select_action(env, player)
        
        # 보드에 플레이어의 선택을 표시
        self.board_a[pos] = player
        if self.print:
            print(player)
            self.print_board()
        # 게임이 종료상태인지 아닌지를 판단
        self.end_check(player)
        
        return  self.reward, self.done
 
    # 현재 보드 상태에서 가능한 행동(둘 수 있는 장소)을 탐색하고 리스트로 반환
    def get_action(self):
        observation = []
        for i in range(25):
            if self.board_a[i] == 0:
                observation.append(i)
        return observation
    
    # 게임이 종료(승패 또는 비김)됐는지 판단
    def end_check(self,player):
        # 0 1 2 3 4 
        # 5 6 7 8 9
        #10 11 12 13 14
        #15 16 17 18 19
        #20 21 22 23 24
        # 승패 조건은 가로, 세로, 대각선 이 -1 이나 1 로 동일할 때 
        end_condition = ((0, 1, 2, 3), (1, 2, 3, 4), (5, 6, 7, 8), (6, 7, 8, 9), \
        (10, 11, 12, 13), (11, 12, 13, 14), (15, 16, 17, 18), (16, 17, 18, 19), \
        (20, 21, 22, 23), (21, 22, 23, 24), (0, 5, 10, 15), (1, 6, 11, 16), (2, 7, 12, 17), \
        (3, 8, 13, 18), (4, 9, 14, 19), (5, 10, 15, 20), (6, 11, 16, 21), (7, 12, 17, 22), \
        (8, 13, 18, 23), (9, 14, 19, 24), (3, 7, 11, 15), (4, 8, 12, 16), (8, 12, 16, 20),\
        (9, 13, 17, 21), (1, 7, 13, 19), (0, 6, 12, 18), (6, 12, 18, 24), (5, 11, 17, 23))
        
        for line in end_condition:
            if self.board_a[line[0]] == self.board_a[line[1]] \
                and self.board_a[line[1]] == self.board_a[line[2]] \
                and self.board_a[line[2]] == self.board_a[line[3]] \
                and self.board_a[line[0]] != 0:
                # 종료됐다면 누가 이겼는지 표시
                self.done = True
                self.reward = player
                return
        # 비긴 상태는 더는 보드에 빈 공간이 없을때
        observation = self.get_action()
        if (len(observation)) == 0:
            self.done = True
            self.reward = 0            
        return
        
    # 현재 보드의 상태를 표시 p1 = O, p2 = X    
    def print_board(self):
        print("+----+----+----+----+----+")
        for i in range(5):
            for j in range(5):
                if self.board_a[5*i+j] == 1:
                    print("|  O",end=" ")
                elif self.board_a[5*i+j] == -1:
                    print("|  X",end=" ")
                else:
                    print("|   ",end=" ")
            print("|")
            print("+----+----+----+----+----+")

            
class Human_player():
    
    def __init__(self):
        self.name = "Human player"
        
    def select_action(self, env, player):
        while True:
            # 가능한 행동을 조사한 후 표시
            available_action = env.get_action()
            print("possible actions = {}".format(available_action))

            # 상태 번호 표시
            print("+----+----+----+----+----+")
            print("+  0 +  1 +  2 +  3 +  4 +")
            print("+----+----+----+----+----+")
            print("+  5 +  6 +  7 +  8 +  9 +")
            print("+----+----+----+----+----+")
            print("+ 10 + 11 + 12 + 13 + 14 +")
            print("+----+----+----+----+----+")
            print("+ 15 + 16 + 17 + 18 + 19 +")
            print("+----+----+----+----+----+")
            print("+ 20 + 21 + 22 + 23 + 24 +")
            print("+----+----+----+----+----+")
                        
            # 키보드로 가능한 행동을 입력 받음
            action = input("Select action(human) : ")
            action = int(action)
            
            # 입력받은 행동이 가능한 행동이면 반복문을 탈출
            if action in available_action:
                return action
            # 아니면 행동 입력을 반복
            else:
                print("You selected wrong action")
        return
    
    
    
class Dong_Monte_Carlo_player():
    
    def __init__(self):
        self.name = "Dong MC player"
        self.num_playout = 100
        self.V_flag = False # 상대방이 이겼을 때 활성화되는 bool형 변수
        self.end_condition = ((0, 1, 2, 3), (1, 2, 3, 4), (5, 6, 7, 8), (6, 7, 8, 9), \
        (10, 11, 12, 13), (11, 12, 13, 14), (15, 16, 17, 18), (16, 17, 18, 19), \
        (20, 21, 22, 23), (21, 22, 23, 24), (0, 5, 10, 15), (1, 6, 11, 16), (2, 7, 12, 17), \
        (3, 8, 13, 18), (4, 9, 14, 19), (5, 10, 15, 20), (6, 11, 16, 21), (7, 12, 17, 22), \
        (8, 13, 18, 23), (9, 14, 19, 24), (3, 7, 11, 15), (4, 8, 12, 16), (8, 12, 16, 20),\
        (9, 13, 17, 21), (1, 7, 13, 19), (0, 6, 12, 18), (6, 12, 18, 24), (5, 11, 17, 23)) # Environment 클래스의 end_condition과 동일

    def select_action(self, env, player):
        available_action = env.get_action()
        V = np.zeros(len(available_action))
        lastTwo = [] # 상대방의 마지막 두 돌을 저장하는 리스트

        global myself # 현재 내가 선공인지 후공인지 알기 위해 선언한 전역 변수
        myself = player # player 정보 할당 (1 또는 -1)

        for i in range(len(available_action)):

            for j in range(self.num_playout):

                temp_env = copy.deepcopy(env)
                self.playout(temp_env, available_action[i], player, lastTwo)
                if self.V_flag: #---------------------------------------------------------------
                    try: #                                                                     -
                        idx1 = available_action.index(lastTwo[0]) #                            -
                        idx2 = available_action.index(lastTwo[1]) #                            - idea_1
                        V[idx1] += 0.05 #                                                      -
                        V[idx2] += 0.05 #                                                      -
                    except: #                                                                  -
                        continue #--------------------------------------------------------------
                elif player == temp_env.reward:
                    V[i] += 1
                    for t in self.end_condition: #----------------------------------------------
                        if available_action[i] in t: #                                         - idea_4
                            V[i] += 0.1 #-------------------------------------------------------

                    if 20 < len(available_action) < 25 and available_action[i] % 2 == 0: #------
                        for e in range(len(available_action)): #                               -
                            if available_action[e] % 2 == 0: #                                 -
                                V[e] += 0.001 #                                                - idea_3
                    elif 20 < len(available_action) < 25 and available_action[i] % 2 == 1: #   -
                        for o in range(len(available_action)): #                               -
                            if available_action[o] % 2 == 1: #                                 -
                                V[o] += 0.001 #-------------------------------------------------

                elif (temp_env.reward == 0) and (myself == -1): #------------------------------- idea_2
                    V[i] += 0.5 #---------------------------------------------------------------

        return available_action[np.argmax(V)]

    def playout(self, temp_env, action, player, lastTwo):
        if len(lastTwo) > 2: # 마지막 두 개의 돌만 저장하기 위해 pop 
            lastTwo.pop(0)

        temp_env.board_a[action] = player
        temp_env.end_check(player)

        if temp_env.done == True:
            if temp_env.reward == -myself: # 상대방이 이겼다면:
                self.V_flag = True # V_flag 활성화
                return
            else: # 내가 이겼거나 비겼으면:
                self.V_flag = False# V_flag 비활성화
                return
        else:
            player = -player
            available_action = temp_env.get_action()
            action_idx = np.random.randint(len(available_action))

            if player == -myself: # 상대방 차례면 action 저장
                lastTwo.append(available_action[action_idx])

            self.playout(temp_env, available_action[action_idx], player, lastTwo)
     


p1 = Dong_Monte_Carlo_player()

p2 = Human_player()
p2.num_playout = 100

auto = False

# auto 모드의 게임수
games = 100

print("pl player : {}".format(p1.name))
print("p2 player : {}".format(p2.name))

# 각 플레이어의 승리 횟수를 저장
p1_score = 0
p2_score = 0
draw_score = 0


if auto: 
    # 자동 모드 실행
    for j in tqdm(range(games)):
        
        np.random.seed(j)
        env = Environment()
        
        for i in range(10000):
            # p1 과 p2가 번갈아 가면서 게임을 진행
            # p1(1) -> p2(-1) -> p1(1) -> p2(-1) ...
            reward, done = env.move(p1,p2,(-1)**i)
            # 게임 종료 체크
            if done == True:
                if reward == 1:
                    p1_score += 1
                elif reward == -1:
                    p2_score += 1
                else:
                    draw_score += 1
                break

else:                
    # 한 게임씩 진행하는 수동 모드
    np.random.seed(1)
    while True:
        
        env = Environment()
        env.print = False
        for i in range(10000):
            reward, done = env.move(p1,p2,(-1)**i)
            env.print_board()
            if done == True:
                if reward == 1:
                    print("winner is p1({})".format(p1.name))
                    p1_score += 1
                elif reward == -1:
                    print("winner is p2({})".format(p2.name))
                    p2_score += 1
                else:
                    print("draw")
                    draw_score += 1
                break
        
        # 최종 결과 출력        
        print("final result")
        env.print_board()

        # 한게임 더?최종 결과 출력 
        answer = input("More Game? (y/n)")

        if answer == 'n':
            break           

print("p1({}) = {} p2({}) = {} draw = {}".format(p1.name, p1_score,p2.name, p2_score,draw_score))