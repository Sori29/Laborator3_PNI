//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "jpeg.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::btnLoadClick(TObject* Sender)
{
    ///-> Load Button
    OpenDialog1->Filter = "Bmp files(*.bmp)|*.BMP|JPEG images\(*.jpg)|*.jpg;";
    if (OpenDialog1->Execute()) {
        if (!FileExists(OpenDialog1->FileName))
            return; // ne asiguram ca s-a selectat un fisier
        AnsiString temp2 = ExtractFileName(OpenDialog1->FileName);
        AnsiString temp = ExtractFileExt(OpenDialog1->FileName);
        AnsiString Ext = temp.LowerCase();
        if (Ext.AnsiPos("jpg") > 0) // este un fisier jpg
        { //-- Decomprima jpeg-ul in imagine bitmap
            TJPEGImage* myjpeg = new TJPEGImage();
            myjpeg->LoadFromFile(OpenDialog1->FileName);
            // creaza o replica de tip bitmap
            myjpeg->DIBNeeded();
            Image1->Picture->Bitmap->Assign(myjpeg);
            delete myjpeg;
        } else if (Ext.AnsiPos("bmp") > 0)
            Image1->Picture->Bitmap->LoadFromFile(OpenDialog1->FileName);
    }
}
void __fastcall TForm1::btnSaveClick(TObject* Sender)
{
    AnsiString Ext;
    // Este necesar sa includem fisierul "jpeg.hpp"
    SaveDialog1->Filter =
        "Bmp files (*.bmp)|*.BMP| JPEG images (*.jpg;*.jpeg)|*.jpg; *;jpeg";
    SaveDialog1->Title = "Save Image";
    SaveDialog1->DefaultExt = "jpg";
    //SaveDialog1->Filter = "JPG|*.jpg";
    //SaveDialog1->Filter = "JPEG images (*.jpg)|*.jpg;|Bmp files\(*.bmp)|*.BMP";
    SaveDialog1->FilterIndex = 1;
    if (SaveDialog1->Execute()) {
        AnsiString temp2 = ExtractFileName(SaveDialog1->FileName);
        AnsiString temp = ExtractFileExt(SaveDialog1->FileName);
        Ext = temp.LowerCase();
    }
    if (Ext.AnsiPos("jpg") > 0) // este un jpg
    { //-- decomprima imaginea jpeg intr-un bitmap.
        TJPEGImage* jp = new TJPEGImage();
        try {
            jp->Assign(Image1->Picture->Bitmap);
            ///Assign() este o metodă a clasei TJPEGImage care atribuie
            ///bitmap-ul de la Image1 obiectului TJPEGImage jp.
            ///Deci jp va conține acum datele de imagine din Imagine1.
            jp->SaveToFile(SaveDialog1->FileName);
        } __finally
        {
            delete jp;
        }
    } else if (Ext.AnsiPos("bmp") > 0)
        Image1->Picture->Bitmap->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::btnZoomInClick(TObject* Sender)
{
    Edit1->Text = (AnsiString)pt[cnt - 1].x + " " + pt[cnt - 2].x + " " +
                  pt[cnt - 1].y + " " + pt[cnt - 2].y;
    ///afiseaza coordonatele selectate
    ///vom avea nevoie de evenimentul MouseDown
    ///coordonatele vor fi salvate TPoint pt[100];
    int ZoomX1 = pt[cnt - 2].x;
    ///coordonatele care definesc dreptunghiul selectat
    int ZoomY1 = pt[cnt - 2].y;
    int ZoomX2 = pt[cnt - 1].x;
    int ZoomY2 = pt[cnt - 1].y;
    int Width = ZoomX2 - ZoomX1;
    int Height = ZoomY2 - ZoomY1;
    Graphics::TBitmap* source = new Graphics::TBitmap;
    source->Assign(Image1->Picture->Bitmap);
    source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;
    // crearea si stabilirea unui bitmap destinatie temporar
    /// in dest se va pastra dreptunghiul selectat
    Graphics::TBitmap* dest = new Graphics::TBitmap;
    dest->Width = pt[cnt - 1].x - pt[cnt - 2].x;
    dest->Height = pt[cnt - 1].y - pt[cnt - 2].y;
    dest->PixelFormat = source->PixelFormat;
    RGBTRIPLE* pixels;
    ///parcurgem bitmap-ul sursa pentru a extrage pixelii de care avem nevoie
	for (int y = pt[cnt - 2].y; y < pt[cnt - 1].y; y++) {
        pixels = (RGBTRIPLE*)source->ScanLine[y];
        for (int x = pt[cnt - 2].x; x < pt[cnt - 1].x; x++)
			dest->Canvas->Pixels[x - pt[cnt - 2].x][y - pt[cnt - 2].y] =
				source->Canvas->Pixels[x][y];
	}
        TRect ZoomRect = Rect(ZoomX1, ZoomY1, ZoomX2, ZoomY2);
        ///un nou obiect cu dimensiuni de 2 ori mai mari decat dest
        TBitmap* ZoomBitmap = new TBitmap;
        ZoomBitmap->Width = Width * 2; /// imaginea va fi marita de 2 ori
        ZoomBitmap->Height = Height * 2;
        /// metoda StretchDraw din canvas va aduce dest la noile dimensiuni
        ZoomBitmap->Canvas->StretchDraw(
            TRect(0, 0, ZoomBitmap->Width, ZoomBitmap->Height), dest);
        ///afisam
        Image2->Picture->Bitmap = ZoomBitmap;
        delete ZoomBitmap;
        delete dest;
        delete source;
        cnt -= 2;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnMozaicClick(TObject* Sender)
{
    TBitmap* src = Image1->Picture->Bitmap;
    src->Assign(Image1->Picture->Bitmap);
    src->PixelFormat = Image1->Picture->Bitmap->PixelFormat;
    TBitmap* dst = new TBitmap;
    dst->Width = src->Width;
    dst->Height = src->Height;
    dst->PixelFormat = src->PixelFormat;
    int mosaicSize = 8; ///poate fi preluata din Edit
    /// Edit5->Text.ToIntDef(0);
    for (int x = 0; x < src->Width; x++) {
        for (int y = 0; y < src->Height; y++) {
            int newX = mosaicSize - x % mosaicSize;
            int newY = mosaicSize - y % mosaicSize;
            // Verifica dacă noile coordonate sunt în limitele imaginii
            if (x + newX > 0 && x + newX < src->Width && y + newY > 0 &&
                y + newY < src->Height)
            {
                TColor color = src->Canvas->Pixels[x + newX][y + newY];
                int r = GetRValue(color);
                int g = GetGValue(color);
                int b = GetBValue(color);
                dst->Canvas->Pixels[x][y] = TColor(RGB(r, g, b));
            } else {
                dst->Canvas->Pixels[x][y] = clWhite;
            }
        }
    }
    Image2->Picture->Bitmap = dst;
    delete dst;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    ///Color->
    if (CheckBox3->Checked) {
        Image1->Canvas->Pen->Color = (TColor)RGB(Edit2->Text.ToIntDef(0),
			Edit3->Text.ToIntDef(0), Edit4->Text.ToIntDef(0));
        IsDrawing = True; ///memebru privat in clasa TForm1,
        ///adica Boolean IsDrawing;
    }
    ////Color<-
    pt[cnt].x = X;
    pt[cnt].y = Y;
    cnt++;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MouseUp(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    ////Color->
    if (CheckBox3->Checked) {
        if (IsDrawing) {
            IsDrawing = False;
        }
    }
    ////Color<-
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MouseMove(
    TObject* Sender, TShiftState Shift, int X, int Y)

{
    ////Color->
    ///de adaugat in form (View as text)-> DoubleBuffered = true;
    ///necesar pentru flickering
    if (CheckBox3->Checked && IsDrawing) {
        Image1->Canvas->Pen->Color = (TColor)RGB(Edit2->Text.ToIntDef(0),
            Edit3->Text.ToIntDef(0), Edit4->Text.ToIntDef(0));
        Image1->Canvas->Brush->Color = (TColor)RGB(Edit2->Text.ToIntDef(0),
            Edit3->Text.ToIntDef(0), Edit4->Text.ToIntDef(0));
        Image1->Canvas->Pen->Style = psSolid; // linie continua
        Image1->Canvas->Pen->Width = Edit1->Text.ToIntDef(1);
        Image1->Canvas->Ellipse(X - 2, Y - 2, X + 2, Y + 2);
    } ////Color<-
}
//---------------------------------------------------------------------------

