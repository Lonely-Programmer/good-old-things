# -*- coding: cp936 -*-
from string import replace
from string import find
from copy import deepcopy

class FamCalc:

    def __init__(self):
        self.parent=['F','M']
        self.child=['T','D']
        self.couple=['Hus','Wif']
        self.sibling=['Bro','Sis']
        self.male=['F','T','Hus','Bro']
        self.female=['M','D','Wif','Sis']
        self.relation1={'父亲':'F','母亲':'M','儿子':'T','女儿':'D','丈夫':'Hus',
                        '妻子':'Wif','兄弟':'Bro','姐妹':'Sis','舅舅':'MBro',
                        '舅母':'MBroWif','姨母':'MSis','姨父':'MSisHus',
                        '姑母':'FSis','姑父':'FSisHus','伯父/叔父':'FBro',
                        '婶婶/伯母':'FBroWif','祖父':'FF','祖母':'FM',
                        '外祖父':'MF','外祖母':'MM','嫂嫂/弟媳':'BroWif',
                        '姐夫/妹夫':'SisHus','侄子':'BroT','侄女':'BroD',
                        '外甥':'SisT','外甥女':'SisD','儿媳':'TWif',
                        '女婿':'DHus','孙子':'TT','孙女':'TD','外孙':'DT',
                        '外孙女':'DD','岳父':'WifF','岳母':'WifM','公公':'HusF',
                        '婆婆':'HusM','自己':''}
        self.relation2={'堂兄弟':('FBroT',),'堂姐妹':('FBroD',),
                        '表兄弟':('FSisT','MBroT','MSisT'),
                        '表姐妹':('FSisD','MBroD','MSisD')}
        for i in ['父亲','母亲','儿子','女儿','祖父','祖母','外祖父','外祖母',
                  '孙子','孙女','外孙','外孙女']:
            print i,
        print
        for i in ['丈夫','妻子','兄弟','姐妹']:
            print i,
        print
        for i in ['岳父','岳母','公公','婆婆']:
            print i,
        print
        for i in ['舅舅','舅母','姨母','姨父','姑母','姑父','伯父/叔父',
                  '婶婶/伯母',]:
            print i,
        print
        for i in ['嫂嫂/弟媳','姐夫/妹夫']:
            print i,
        print
        for i in ['侄子','侄女','外甥','外甥女']:
            print i,
        print
        print

    def gender(self,element):
        if element in self.male:
            return 0
        if element in self.female:
            return 1

    def preSeek(self,ans,obj):
        pos=find(ans,obj)
        if pos==-1:
            return 'NotFound'
        if pos==0:
            return 'E'
        elif 'A'<=ans[pos-1]<='Z':
            return ans[pos-1]
        else:
            return ans[pos-3:pos]          

    def checkErr(self,ans):
        for i in self.male:
            if i+'Hus' in ans:
                return 'ERROR'
        for k in self.female:
            if k+'Wif' in ans:
                return 'ERROR'
        return ans

    def valley(self,ans):
        for i in self.parent:
            for j in self.child:
                for k in self.parent:
                    while i+j+k in ans:
                        ans=replace(ans,i+j+k,k)
        for i in self.sibling:
            for k in self.parent:
                while i+k in ans:
                    ans=replace(ans,i+k,k)
        return ans

    def summit(self,ans):
        for i in self.child:
            for j in self.parent:
                for k in self.child:
                    while i+j+k in ans:
                        ans=replace(ans,i+j+k,k)
        for i in self.couple:
            for k in self.child:
                while i+k in ans:
                    ans=replace(ans,i+k,k)
        return ans

    def coupleElim(self,ans):
        ans=replace(ans,'HusWif','')
        ans=replace(ans,'WifHus','')
        return ans

    def siblingElim(self,ans):
        while True:
            p=deepcopy(ans)
            for temp in ans:
                for i in self.sibling:
                    for k in self.sibling:
                        toFind=i+k
                        prev=self.preSeek(temp,toFind)
                        if prev=='NotFound':
                            continue
                        pos=find(temp,toFind)
                        posTemp=ans.index(temp)
                        if prev=='E' or self.gender(prev)==self.gender(k):                         
                            ans.append(temp[:pos]+temp[pos+6:])
                            ans.append(temp[:pos]+temp[pos+3:])
                        else:
                            ans.append(temp[:pos]+temp[pos+3:])
                        del ans[posTemp]
                        return self.siblingElim(ans)
            if set(p)==set(ans):
                p=list(set(p))
                return p
    def generationElim1(self,ans):
        while True:
            p=deepcopy(ans)
            for temp in ans:
                for i in self.parent:
                    for k in self.child:
                        toFind=i+k
                        prev=self.preSeek(temp,toFind)
                        if prev=='NotFound':
                            continue
                        pos=find(temp,toFind)
                        posTemp=ans.index(temp)
                        if self.gender(k)==0:
                            relation='Bro'
                        else:
                            relation='Sis'
                        if prev=='E' or self.gender(prev)==self.gender(k):
                            ans.append(temp[:pos]+temp[pos+2:])
                            ans.append(temp[:pos]+relation+temp[pos+2:])
                        else:
                            ans.append(temp[:pos]+relation+temp[pos+2:])
                        del ans[posTemp]
                        return self.generationElim1(ans)
            if set(p)==set(ans):
                p=list(set(p))
                return p

    def generationElim2(self,ans):
        while True:
            p=deepcopy(ans)
            for temp in ans:
                for i in self.child:
                    for k in self.parent:
                        toFind=i+k
                        prev=self.preSeek(temp,toFind)
                        if prev=='NotFound':
                            continue
                        pos=find(temp,toFind)
                        posTemp=ans.index(temp)
                        if self.gender(k)==0:
                            relation='Hus'
                        else:
                            relation='Wif'
                        if prev=='E' or self.gender(prev)==self.gender(k):
                            ans.append(temp[:pos]+temp[pos+2:])
                            ans.append(temp[:pos]+relation+temp[pos+2:])
                        else:
                            ans.append(temp[:pos]+relation+temp[pos+2:])
                        del ans[posTemp]
                        return self.generationElim2(ans)
            if set(p)==set(ans):
                p=list(set(p))
                return p
    
    def calc(self,ans):
        while True:
            p=ans
            for temp in ans:
                ans=self.checkErr(ans)
                ans=self.valley(ans)
                ans=self.summit(ans)
                ans=self.coupleElim(ans)
            if set(p)==set(ans):
                break
        ans=[ans]
        while True:
            p=deepcopy(ans)
            ans=self.siblingElim(ans)
            ans=self.generationElim1(ans)
            ans=self.generationElim2(ans)
            if set(p)==set(ans):
                break
        while True:
            p=deepcopy(ans)
            for i in range(len(ans)):
                ans[i]=self.checkErr(ans[i])
                ans[i]=self.valley(ans[i])
                ans[i]=self.summit(ans[i])
                ans[i]=self.coupleElim(ans[i])
            if set(p)==set(ans):
                p=list(set(p))
                while 'ERROR' in p:
                    p.remove('ERROR')
                return p
                
    def analyze(self,char):
        temp=char.split('的')
        for i in range(len(temp)):
            temp[i]=self.relation1[temp[i]]
        s=''
        for i in range(len(temp)):
            s+=temp[i]
        result=self.calc(s)
        answer=''
        print result
        for i in result:
            for k in self.relation1.keys():
                if i==self.relation1[k]:
                    answer=answer+' '+k
            for k in self.relation2.keys():
                if i in self.relation2[k]:
                    answer=answer+' '+k
            answer+='\n'
        return answer              

def main():
    a=FamCalc()
    while True:
        try:
            print a.analyze(raw_input('请输入(若称谓带斜杠，则需输入带斜杠的两个称谓)\n'))
        except:
            print '请检查你的输入(若称谓带斜杠，则需输入带斜杠的两个称谓)\n'

main()
