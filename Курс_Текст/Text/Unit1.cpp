//---------------------------------------------------------------------------

#include <vcl.h>
#include<io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define NL 3
#define NS 20
#define NW 20
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Clear();
	Memo2->Clear();
    Memo3->Clear();
}

AnsiString TX, FileNameRez;
FILE* Text_TX;
String str;
int count=0;
int maxi=0;
char maxch;
TStringList * MyList=new TStringList();
TStringList * ptStrintList=new TStringList();
void Out(TStringList * MyList,int n,int i,TMemo *Memo1){
	String s = MyList[0][i];
	if(s.Pos('.')){
	   int index = s.Pos('.')-1;
	   s=s.SubString(0, index);
	   Memo1->Lines->Add(IntToStr(n)+". "+s);
	}
	else if(s.Pos('!')){
		int index = s.Pos('!')-1;
		s=s.SubString(0, index);
		Memo1->Lines->Add(IntToStr(n)+". "+s);
	}
	else if(s.Pos(',')){
		int index = s.Pos(',')-1;
		s=s.SubString(0, index);
		Memo1->Lines->Add(IntToStr(n)+". "+s);
	}
	else if(s.Pos('?')){
		int index = s.Pos('?')-1;
		s=s.SubString(0, index);
		Memo1->Lines->Add(IntToStr(n)+". "+s);
	}
	else if(s.Pos(':')){
		int index = s.Pos(':')-1;
		s=s.SubString(0, index);
		Memo1->Lines->Add(IntToStr(n)+". "+s);
	}
	else
	   Memo1->Lines->Add(IntToStr(n)+". "+s);
}

void Maximum(TStringList *MyList){
	String buff1, buff2;
	for(int i=0; i<MyList->Count;i++){
		buff1= MyList[0][i];
		buff1=buff1.SubString(0,1);
		char * s1=AnsiString(buff1).c_str();
		for(int j=0;j<MyList->Count;j++){
			buff2= MyList[0][j];
			buff2=buff2.SubString(0,1);
			char * s2=AnsiString(buff2).c_str();
			if(s1==s2){
				count++;
			}
		}
		if(maxi<count){
			maxi=count;
			maxch=*s1;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{

	OpenDialog1->Title="������� ����";
	if (OpenDialog1->Execute()) {
		TX=OpenDialog1->FileName;
		if((Text_TX=fopen(TX.c_str(),"rb"))==NULL){
			ShowMessage("������ �������� �����"); return;
		}
		 Memo1->Lines->LoadFromFile(TX,TEncoding::UTF8);
	}

	ptStrintList->LoadFromFile(TX,TEncoding::UTF8);
	for(int i=0; i<ptStrintList->Count; i++){
		str+=ptStrintList[0][i];
	}
	str=str.LowerCase();
    MyList->StrictDelimiter = true;
	MyList->Delimiter = ' ';
	MyList->DelimitedText=str;
	Maximum(MyList);
	fclose(Text_TX);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	SaveDialog1->Title="��������� ���� �����������";
	if(FileNameRez!=""){
	   Memo2->Lines->SaveToFile(FileNameRez);
	}
	else
	if (SaveDialog1->Execute()) {
		FileNameRez = SaveDialog1->FileName;
		Memo2->Lines->SaveToFile(FileNameRez);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int n=0;
	String buff;
	for(int i=0; i<ptStrintList->Count;i++)
		Memo2->Lines->Add(ptStrintList[0][i]);
	for(int i=0; i<MyList->Count;i++){
		buff= MyList[0][i];
		buff=buff.SubString(0,1);
		char* s3 = AnsiString(buff).c_str();
		if(*s3 == maxch){
			n++;
			Out(MyList,n,i,Memo2);
		}
	}
   MyList->Free();
   ptStrintList->Free();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Memo3->Lines->Add("���������� ��������� - ������ �.�.");
}
//---------------------------------------------------------------------------

