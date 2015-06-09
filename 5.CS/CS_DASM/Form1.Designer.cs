namespace CS_DASM
{
    partial class DASM_MAIN
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DASM_MAIN));
            this.DASMMainMenu = new System.Windows.Forms.MenuStrip();
            this.파일FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DumpMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.TreeviewMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ExitMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.보기VToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.도움말HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.HelpMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DASMInfoMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DASMTreeView = new System.Windows.Forms.TreeView();
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.DASMopenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.richTextBox = new System.Windows.Forms.RichTextBox();
            this.DASMMainMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // DASMMainMenu
            // 
            this.DASMMainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일FToolStripMenuItem,
            this.보기VToolStripMenuItem,
            this.도움말HToolStripMenuItem});
            this.DASMMainMenu.Location = new System.Drawing.Point(0, 0);
            this.DASMMainMenu.Name = "DASMMainMenu";
            this.DASMMainMenu.Size = new System.Drawing.Size(494, 24);
            this.DASMMainMenu.TabIndex = 0;
            this.DASMMainMenu.Text = "menuStrip1";
            // 
            // 파일FToolStripMenuItem
            // 
            this.파일FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OpenMenuItem,
            this.DumpMenuItem,
            this.TreeviewMenuItem,
            this.ExitMenuItem});
            this.파일FToolStripMenuItem.Name = "파일FToolStripMenuItem";
            this.파일FToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.파일FToolStripMenuItem.Text = "파일(&F)";
            // 
            // OpenMenuItem
            // 
            this.OpenMenuItem.Name = "OpenMenuItem";
            this.OpenMenuItem.Size = new System.Drawing.Size(156, 22);
            this.OpenMenuItem.Text = "열기(&O)";
            this.OpenMenuItem.Click += new System.EventHandler(this.OpenMenuItem_Click);
            // 
            // DumpMenuItem
            // 
            this.DumpMenuItem.Name = "DumpMenuItem";
            this.DumpMenuItem.Size = new System.Drawing.Size(156, 22);
            this.DumpMenuItem.Text = "덤프(&D)";
            // 
            // TreeviewMenuItem
            // 
            this.TreeviewMenuItem.Name = "TreeviewMenuItem";
            this.TreeviewMenuItem.Size = new System.Drawing.Size(156, 22);
            this.TreeviewMenuItem.Text = "트리 뷰 덤프(&T)";
            // 
            // ExitMenuItem
            // 
            this.ExitMenuItem.Name = "ExitMenuItem";
            this.ExitMenuItem.Size = new System.Drawing.Size(156, 22);
            this.ExitMenuItem.Text = "종료(&X)";
            // 
            // 보기VToolStripMenuItem
            // 
            this.보기VToolStripMenuItem.Name = "보기VToolStripMenuItem";
            this.보기VToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.보기VToolStripMenuItem.Text = "보기(&V)";
            // 
            // 도움말HToolStripMenuItem
            // 
            this.도움말HToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.HelpMenuItem,
            this.DASMInfoMenuItem});
            this.도움말HToolStripMenuItem.Name = "도움말HToolStripMenuItem";
            this.도움말HToolStripMenuItem.Size = new System.Drawing.Size(72, 20);
            this.도움말HToolStripMenuItem.Text = "도움말(&H)";
            // 
            // HelpMenuItem
            // 
            this.HelpMenuItem.Name = "HelpMenuItem";
            this.HelpMenuItem.Size = new System.Drawing.Size(137, 22);
            this.HelpMenuItem.Text = "도움말";
            // 
            // DASMInfoMenuItem
            // 
            this.DASMInfoMenuItem.Name = "DASMInfoMenuItem";
            this.DASMInfoMenuItem.Size = new System.Drawing.Size(137, 22);
            this.DASMInfoMenuItem.Text = "DASM 정보";
            // 
            // DASMTreeView
            // 
            this.DASMTreeView.ImageIndex = 0;
            this.DASMTreeView.ImageList = this.imageList;
            this.DASMTreeView.Location = new System.Drawing.Point(0, 24);
            this.DASMTreeView.Name = "DASMTreeView";
            this.DASMTreeView.SelectedImageIndex = 0;
            this.DASMTreeView.Size = new System.Drawing.Size(494, 277);
            this.DASMTreeView.TabIndex = 1;
            this.DASMTreeView.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.DASMTreeView_NodeMouseDoubleClick);
            // 
            // imageList
            // 
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList.Images.SetKeyName(0, "FilePath.bmp");
            this.imageList.Images.SetKeyName(1, "SystemIcon.bmp");
            this.imageList.Images.SetKeyName(2, "Project.bmp");
            this.imageList.Images.SetKeyName(3, "Class.bmp");
            this.imageList.Images.SetKeyName(4, "Property.bmp");
            this.imageList.Images.SetKeyName(5, "Static변수.bmp");
            this.imageList.Images.SetKeyName(6, "Static함수.bmp");
            this.imageList.Images.SetKeyName(7, "함수.bmp");
            // 
            // DASMopenFileDialog
            // 
            this.DASMopenFileDialog.FileName = "DASMopenFileDialog";
            // 
            // richTextBox
            // 
            this.richTextBox.Location = new System.Drawing.Point(0, 308);
            this.richTextBox.Name = "richTextBox";
            this.richTextBox.Size = new System.Drawing.Size(494, 220);
            this.richTextBox.TabIndex = 2;
            this.richTextBox.Text = "";
            // 
            // DASM_MAIN
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(494, 529);
            this.Controls.Add(this.richTextBox);
            this.Controls.Add(this.DASMTreeView);
            this.Controls.Add(this.DASMMainMenu);
            this.MainMenuStrip = this.DASMMainMenu;
            this.Name = "DASM_MAIN";
            this.Text = "DASM";
            this.Load += new System.EventHandler(this.DASM_MAIN_Load);
            this.Shown += new System.EventHandler(this.DASM_MAIN_Shown);
            this.DASMMainMenu.ResumeLayout(false);
            this.DASMMainMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip DASMMainMenu;
        private System.Windows.Forms.ToolStripMenuItem 파일FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem OpenMenuItem;
        private System.Windows.Forms.ToolStripMenuItem DumpMenuItem;
        private System.Windows.Forms.ToolStripMenuItem TreeviewMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ExitMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 보기VToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 도움말HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem HelpMenuItem;
        private System.Windows.Forms.ToolStripMenuItem DASMInfoMenuItem;
        private System.Windows.Forms.TreeView DASMTreeView;
        private System.Windows.Forms.OpenFileDialog DASMopenFileDialog;
        private System.Windows.Forms.ImageList imageList;
        private System.Windows.Forms.RichTextBox richTextBox;
    }
}

