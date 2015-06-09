using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ILLib;

namespace CS_DASM
{
    public partial class DASM_MAIN : Form
    {
        public DASM_MAIN()
        {
            GlobalStatic.LoadOpcode();
            InitializeComponent();
        }
        private void OpenMenuItem_Click(object sender, EventArgs e)
        {
            this.DASMopenFileDialog.Filter = "exe files (*.exe)|*.exe|All files (*.*)|*.*";
            DASMopenFileDialog.FilterIndex = 1;
            DASMopenFileDialog.RestoreDirectory = true;

            DASMopenFileDialog.ShowDialog();

            //Assembly asm = Assembly.LoadFile(DASMopenFileDialog.FileName);

            //-- 파일 오픈
            AssemblyInfo asminfo = new AssemblyInfo(DASMopenFileDialog.FileName, ref this.DASMTreeView);
            //--
            DASMopenFileDialog.Dispose();
        }
        private Bitmap m_Icon;
        private Bitmap[] m_Icons;

        private void DASM_MAIN_Load(object sender, EventArgs e)
        {
            Type targetType = typeof(Properties.Resources);
            foreach (PropertyInfo property in targetType.GetProperties())
            {
                if(property.Name.Equals("ICON"))
                {
                    
                }
            }
        }
        
        private void DASM_MAIN_Shown(object sender, EventArgs e)
        {
            m_Icon = new Bitmap(Properties.Resources.ICON);
            m_Icons = new Bitmap[8];
            int width = m_Icon.Width;
            int nw = width / 8;
            int height = m_Icon.Height;
            Size size = m_Icon.Size;
            Rectangle rect = new Rectangle(0,0,nw,height);
            
        }

        private void DASMTreeView_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            TreeView temp = (TreeView)sender;
            MethodInfo mtemp;
            ILCodeReader reader;
            if(e.Node.Tag != null)
            {
                mtemp = AssemblyInfo.m_methods.ElementAt((int)e.Node.Tag);
                reader = new ILCodeReader(AssemblyInfo.modules[1], mtemp.GetMethodBody().GetILAsByteArray());
                this.richTextBox.Text = "";
                string str;
                foreach (ILInstruct item in reader.m_ILInstructs)
	            {
                    str = mtemp.Name+"_"+item.Offset + " : " + item.Opcode;
                    if(item.Operand != null)
                        str += ", operand: " + item.Operand.ToString();
                    str += "\n";

                    this.richTextBox.Text += str;
	            }
            }
            else
            {
                this.richTextBox.Text += "함수 본문을 찾을 수 없음";
            }
            
        }
    }
}
