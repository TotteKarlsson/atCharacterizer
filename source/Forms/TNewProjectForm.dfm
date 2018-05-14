object NewProjectForm: TNewProjectForm
  Left = 0
  Top = 0
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
    object UserE: TSTDStringLabeledEdit
      Left = 18
      Top = 85
      Width = 121
      Height = 21
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'User'
      TabOrder = 1
    end
    object ProjectNameE: TSTDStringLabeledEdit
      Left = 16
      Top = 41
      Width = 121
      Height = 21
      EditLabel.Width = 63
      EditLabel.Height = 13
      EditLabel.Caption = 'Project name'
      TabOrder = 2
      Text = 'MyProject'
      Value = 'MyProject'
    end
    object Button3: TButton
      Left = 536
      Top = 39
      Width = 41
      Height = 25
      Hint = 'Open|Opens an existing file'
      Caption = '...'
      ImageIndex = 7
      TabOrder = 3
      OnClick = Button3Click
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 112
      Width = 185
      Height = 180
      Caption = 'Categories'
      TabOrder = 4
      object CategoryLB: TListBox
        Left = 2
        Top = 15
        Width = 181
        Height = 122
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
      end
      object Panel2: TPanel
        Left = 2
        Top = 137
        Width = 181
        Height = 41
        Align = alBottom
        TabOrder = 1
        object AddCategoryBtn: TButton
          Left = 8
          Top = 6
          Width = 63
          Height = 27
          Caption = 'Add'
          TabOrder = 0
          OnClick = AddCategoryBtnClick
        end
        object Button4: TButton
          Left = 96
          Top = 6
          Width = 63
          Height = 27
          Caption = 'Clear'
          TabOrder = 1
          OnClick = Button4Click
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 295
    Width = 635
    Height = 41
    Align = alBottom
    TabOrder = 1
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
    Left = 376
    Top = 96
    object BrowseForFolder1: TBrowseForFolder
      Category = 'File'
      Caption = '...'
      DialogCaption = '...'
      BrowseOptions = []
      BrowseOptionsEx = []
    end
  end
  object FileOpenDialog1: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoPathMustExist]
    OnFileOkClick = FileOpenDialog1FileOkClick
    Left = 288
    Top = 160
  end
end
