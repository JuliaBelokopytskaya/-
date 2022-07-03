//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
  randomize();
}
//---------------------------------------------------------------------------

struct Stack {
	int info;
	Stack * next;
	}*start, *t;
//----------------------------------------------------------------------------
Stack* InStack(Stack*, int);
void View(Stack*);
void Del_All(Stack **);
Stack*  Del_Odd(Stack*);

//---------------------------------------------------------------------------
Stack* InStack(Stack *p, int in) {
Stack *t = new Stack;
t -> info = in;
t -> next = p;
return t;
}
//------------------------------------------------------------------
void View(Stack *p) {
	Stack *t = p;
	while( t != NULL) {
		Form1->Memo1->Lines->Add(" " + IntToStr( t->info));
		t = t -> next;
	}
}
//-----------------------------------------------------------
void Del_All(Stack **p) {
	while(*p != NULL) {
		t = *p;
		*p = (*p) -> next;
		delete t;
	}
}
//-----------------------------------------------------------
Stack* Del_Odd(Stack *p)
{
	Stack *r=NULL;
	if(p==NULL)
		return NULL;
	if(p->next!=NULL)
		r=Del_Odd(p->next);
	if(p->info % 2 == 0 && p->info > 0)
	{
		delete p;
        return r;
    }
    else
	{
		p->next=r;
		return p;
	}
  }
//-----------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int i, in, n = StrToInt(Edit1->Text);
	if(start != NULL){
		ShowMessage("���������� ������!");
		return;
	}
	for(i = 1; i <= n; i++){
		in = random(20) + 1;
		start = InStack(start, in);
	}
	Tag += n;
	Memo1->Lines->Add("������� " + IntToStr(n) + " ���������.");
}
//-----------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    int i, in, n = StrToInt(Edit1->Text);
	for(i = 1; i <= n; i++){
		in = random(20) + 1;
		start = InStack(start, in);
	}
	Memo1->Lines->Add("�������� " + IntToStr(n) + " ���������.");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if(!start){
		ShowMessage("���� ����!");
		Memo1->Lines->Add("���� ����!");
		return;
	}
	Memo1->Lines->Add("--- �������� ---");
	View(start);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	if (start != NULL) Del_All(&start);
	ShowMessage("������ �����������!");
	Memo1->Lines->Add("������ �����������!");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	start = Del_Odd(start);
	Memo1->Lines->Add("--- �������� ---");
	View(start);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	if(start != NULL) Del_All(&start);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Memo1->Clear();
}
//---------------------------------------------------------------------------

