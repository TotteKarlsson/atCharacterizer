object NewProjectForm: TNewProjectForm
  Left = 0
  Top = 0
  ActiveControl = IntegerLabeledEdit1
  BorderStyle = bsSizeToolWin
  Caption = 'New Project Properties'
  ClientHeight = 336
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 635
    Height = 295
    Align = alClient
    Caption = 'Project '
    TabOrder = 0
    ExplicitLeft = 160
    ExplicitTop = 40
    ExplicitWidth = 185
    ExplicitHeight = 105
    object ImageFolderE: TSTDStringLabeledEdit
      Left = 168
      Top = 41
      Width = 362
      Height = 21
      EditLabel.Width = 63
      EditLabel.Height = 13
      EditLabel.Caption = 'Image Folder'
      TabOrder = 0
    end
    object IntegerLabeledEdit1: TIntegerLabeledEdit
      Left = 168
      Top = 109
      Width = 121
      Height = 21
      EditLabel.Width = 89
      EditLabel.Height = 13
      EditLabel.Caption = 'Number of Classes'
      TabOrder = 1
      Text = '3'
      Value = 3
    end
    object UserE: TSTDStringLabeledEdit
      Left = 16
      Top = 109
      Width = 121
      Height = 21
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'User'
      TabOrder = 2
    end
    object ProjectNameE: TSTDStringLabeledEdit
      Left = 16
      Top = 41
      Width = 121
      Height = 21
      EditLabel.Width = 63
      EditLabel.Height = 13
      EditLabel.Caption = 'Project name'
      TabOrder = 3
      Text = 'MyProject'
      Value = 'MyProject'
    end
    object Button3: TButton
      Left = 536
      Top = 39
      Width = 41
      Height = 25
      Action = BrowseForFolder1
      TabOrder = 4
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 295
    Width = 635
    Height = 41
    Align = alBottom
    TabOrder = 1
    ExplicitLeft = 296
    ExplicitWidth = 185
    object Button1: TButton
      Left = 432
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object Button2: TButton
      Left = 536
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Create'
      ModalResult = 1
      TabOrder = 1
    end
  end
  object ActionList1: TActionList
    Left = 88
    Top = 192
    object BrowseForFolder1: TBrowseForFolder
      Category = 'File'
      Caption = '...'
      DialogCaption = '...'
      BrowseOptions = []
      BrowseOptionsEx = []
      BeforeExecute = BrowseForFolder1BeforeExecute
      OnAccept = BrowseForFolder1Accept
    end
  end
end
