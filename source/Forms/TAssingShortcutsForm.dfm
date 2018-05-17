object AssignShortCutsForm: TAssignShortCutsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Keys'
  ClientHeight = 253
  ClientWidth = 243
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Grid: TStringGrid
    Left = 0
    Top = 0
    Width = 243
    Height = 205
    Align = alClient
    ColCount = 2
    TabOrder = 0
    OnGetEditMask = GridGetEditMask
    OnGetEditText = GridGetEditText
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object Panel1: TPanel
    Left = 0
    Top = 205
    Width = 243
    Height = 48
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      243
      48)
    object Button1: TButton
      Left = 157
      Top = 8
      Width = 75
      Height = 33
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object Button2: TButton
      Left = 69
      Top = 8
      Width = 75
      Height = 33
      Anchors = [akTop, akRight]
      Caption = 'Ok'
      ModalResult = 1
      TabOrder = 1
    end
  end
end
