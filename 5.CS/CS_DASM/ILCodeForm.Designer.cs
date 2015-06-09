namespace CS_DASM
{
    partial class ILCodeForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ILCodeMenuStrip = new System.Windows.Forms.MenuStrip();
            this.FindMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ILRichTextBox = new System.Windows.Forms.RichTextBox();
            this.ILCodeMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // ILCodeMenuStrip
            // 
            this.ILCodeMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FindMenuItem});
            this.ILCodeMenuStrip.Location = new System.Drawing.Point(0, 0);
            this.ILCodeMenuStrip.Name = "ILCodeMenuStrip";
            this.ILCodeMenuStrip.Size = new System.Drawing.Size(437, 24);
            this.ILCodeMenuStrip.TabIndex = 0;
            this.ILCodeMenuStrip.Text = "menuStrip1";
            // 
            // FindMenuItem
            // 
            this.FindMenuItem.Name = "FindMenuItem";
            this.FindMenuItem.Size = new System.Drawing.Size(43, 20);
            this.FindMenuItem.Text = "찾기";
            // 
            // ILRichTextBox
            // 
            this.ILRichTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ILRichTextBox.Location = new System.Drawing.Point(0, 24);
            this.ILRichTextBox.Name = "ILRichTextBox";
            this.ILRichTextBox.Size = new System.Drawing.Size(437, 344);
            this.ILRichTextBox.TabIndex = 1;
            this.ILRichTextBox.Text = "";
            // 
            // ILCodeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(437, 368);
            this.Controls.Add(this.ILRichTextBox);
            this.Controls.Add(this.ILCodeMenuStrip);
            this.MainMenuStrip = this.ILCodeMenuStrip;
            this.Name = "ILCodeForm";
            this.Text = "ILCodeForm";
            this.ILCodeMenuStrip.ResumeLayout(false);
            this.ILCodeMenuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip ILCodeMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem FindMenuItem;
        private System.Windows.Forms.RichTextBox ILRichTextBox;
    }
}