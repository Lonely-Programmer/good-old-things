# -*- coding: utf-8 -*-
import random
import copy

class Game:

    def __init__(self):
        while True:
            order=int(input("Please enter the order(2-100)\n"))
            if 1<order<101:
                break
        self.score=[0]
        self.points=0
        self.order=order
        self.record={}
        self.matrix=[[0 for i in xrange(self.order)] for i in xrange(self.order)]
        self.matrix=self.randBlock(self.matrix)
        self.matrix=self.randBlock(self.matrix)
        self.counter=0
        self.won=False
        self.record[0]=copy.deepcopy(self.matrix)
        self.outBlock(self.matrix)

    def zeroTop(self,lst):
        mat=copy.deepcopy(lst)
        zeroNum=mat.count(0)
        while mat.count(0)>0:
            mat.remove(0)
        return zeroNum*[0]+mat

    def combine(self,lst):
        mat=copy.deepcopy(lst)
        for i in range(len(mat)-1,0,-1):
            if mat[i]==mat[i-1]:
                mat[i]=mat[i]+mat[i-1]
                mat[i-1]=0
                self.points+=mat[i]
                mat=self.zeroTop(mat)
        return mat

    def rightward(self,matrix):
        mat=copy.deepcopy(matrix)
        for i in range(0,len(mat)):
            mat[i]=self.combine(self.zeroTop(mat[i]))
        return mat

    def leftward(self,matrix):
        mat=copy.deepcopy(matrix)
        for i in range(0,len(mat)):
            mat[i].reverse()
            mat[i]=self.combine(self.zeroTop(mat[i]))
            mat[i].reverse()
        return mat

    def trn(self,matrix):
        mat=copy.deepcopy(matrix)
        for i in range(0,len(mat)):
            for j in range(0,i):
                mat[i][j],mat[j][i]=mat[j][i],mat[i][j]
        return mat

    def downward(self,matrix):
        mat=copy.deepcopy(matrix)
        mat=self.trn(mat)
        mat=self.rightward(mat)
        mat=self.trn(mat)
        return mat

    def upward(self,matrix):
        mat=copy.deepcopy(matrix)
        mat=self.trn(mat)
        mat=self.leftward(mat)
        mat=self.trn(mat)
        return mat

    def moveBlock(self,matrix,direction):
        mat=copy.deepcopy(matrix)
        self.points=0
        if direction=="w":
            return self.upward(mat)
        elif direction=="s":
            return self.downward(mat)
        elif direction=="a":
            return self.leftward(mat)
        elif direction=="d":
            return self.rightward(mat)

    def randBlock(self,matrix):
        mat=copy.deepcopy(matrix)
        if random.random<0.1:
            appearNum=4
        else:
            appearNum=2
        length=len(mat)
        while True:
            row=random.randrange(0,length)
            col=random.randrange(0,length)
            if mat[row][col]==0:
                mat[row][col]=appearNum
                return mat

    def upAble(self,matrix):
        mat=copy.deepcopy(matrix)
        mat=self.upward(mat)
        if mat==matrix:
            return False
        else:
            return True

    def downAble(self,matrix):
        mat=copy.deepcopy(matrix)
        mat=self.downward(mat)
        if mat==matrix:
            return False
        else:
            return True

    def leftAble(self,matrix):
        mat=copy.deepcopy(matrix)
        mat=self.leftward(mat)
        if mat==matrix:
            return False
        else:
            return True

    def rightAble(self,matrix):
        mat=copy.deepcopy(matrix)
        mat=self.rightward(mat)
        if mat==matrix:
            return False
        else:
            return True

    def moveAble(self,matrix):
        mat=copy.deepcopy(matrix)
        if self.upAble(mat) or self.downAble(mat) or self.leftAble(mat) or self.rightAble(mat):
            return True
        else:
            return False

    def winBlock(self,matrix):
        mat=copy.deepcopy(matrix)
        temp=[]
        for i in range(0,len(mat)):
            temp=temp+mat[i]
        if 2048 in temp:
            return "win"
        elif self.moveAble(mat):
            return "playing"
        else:
            return "lose"

    def outBlock(self,matrix):
        for i in range(0,len(matrix)):
            print matrix[i]
        print "Your score:%d" % (self.score[self.counter])

    def play(self):
        while True:
            temp=copy.deepcopy(self.matrix)
            direction=raw_input("direction:w/s/a/d,z to undo\n>>>").lower()
            if direction in ["w","s","a","d"]:
                self.matrix=self.moveBlock(self.matrix,direction)
                if temp!=self.matrix:
                    self.matrix=self.randBlock(self.matrix)
                    self.counter+=1
                    self.record[self.counter]=copy.deepcopy(self.matrix)
                    self.score.append(self.score[-1]+self.points)
                else:
                    print "This move has no efficiency!"
            elif direction=="z":
                if self.counter>0:
                    self.counter-=1
                    self.matrix=copy.deepcopy(self.record[self.counter])
                    del self.record[self.counter]
                    del self.score[-1]
                else:
                    print "Cannot undo anymore!"
            else:
                print "Wrong input!"
            self.outBlock(self.matrix)
            if self.winBlock(self.matrix)=="win" and not(self.won):
                    print "You win!"
                    self.won=True
            if self.winBlock(self.matrix)=="lose":
                print "Game Over!"
                break

def main():
    p=Game()
    p.play()

main()
