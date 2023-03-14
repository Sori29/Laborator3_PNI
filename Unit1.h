//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TImage *Image1;
	TSaveDialog *SaveDialog1;
	TImage *Image2;
	TButton *btnLoad;
	TButton *btnMozaic;
	TButton *btnZoomIn;
	TButton *btnZoomOut;
	TButton *btnSave;
	TEdit *Edit1;
	TLabel *Label1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TCheckBox *CheckBox3;
	void __fastcall btnLoadClick(TObject *Sender);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall btnZoomInClick(TObject *Sender);
	void __fastcall btnMozaicClick(TObject *Sender);
	void __fastcall MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
private:
Boolean IsDrawing;
public:
		TPoint pt[100];
    	int cnt = 0;
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
