object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 687
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 305
    Height = 289
    OnMouseDown = MouseDown
    OnMouseMove = MouseMove
    OnMouseUp = MouseUp
  end
  object Image2: TImage
    Left = 422
    Top = 8
    Width = 257
    Height = 289
  end
  object Label1: TLabel
    Left = 360
    Top = 368
    Width = 29
    Height = 15
    Caption = 'Color'
  end
  object btnLoad: TButton
    Left = 328
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Load'
    TabOrder = 0
    OnClick = btnLoadClick
  end
  object btnMozaic: TButton
    Left = 568
    Top = 328
    Width = 75
    Height = 25
    Caption = 'Mozaic'
    TabOrder = 1
    OnClick = btnMozaicClick
  end
  object btnZoomIn: TButton
    Left = 16
    Top = 328
    Width = 75
    Height = 25
    Caption = 'Zoom in'
    TabOrder = 2
    OnClick = btnZoomInClick
  end
  object btnZoomOut: TButton
    Left = 128
    Top = 328
    Width = 75
    Height = 25
    Caption = 'Zoom out'
    TabOrder = 3
  end
  object btnSave: TButton
    Left = 328
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 4
    OnClick = btnSaveClick
  end
  object Edit1: TEdit
    Left = 304
    Top = 329
    Width = 121
    Height = 23
    TabOrder = 5
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 224
    Top = 400
    Width = 121
    Height = 23
    TabOrder = 6
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 353
    Top = 400
    Width = 121
    Height = 23
    TabOrder = 7
    Text = 'Edit3'
  end
  object Edit4: TEdit
    Left = 480
    Top = 400
    Width = 121
    Height = 23
    TabOrder = 8
    Text = 'Edit4'
  end
  object CheckBox3: TCheckBox
    Left = 319
    Top = 144
    Width = 97
    Height = 17
    Caption = 'CheckBox3'
    TabOrder = 9
  end
  object OpenDialog1: TOpenDialog
    Left = 8
    Top = 400
  end
  object SaveDialog1: TSaveDialog
    Left = 72
    Top = 400
  end
end
