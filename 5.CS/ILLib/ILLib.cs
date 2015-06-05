using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection.Emit;
using System.Reflection;

namespace ILLib
{
    /// <summary>
    /// 명령어를 하나 저장하는 저장소
    /// </summary>
    public class ILInstruct
    {
        
        OpCode opcode;
        object operand = null;

        public ILInstruct() { }
        //public ILInstruct() { }

    }

    /// <summary>
    /// 전역변수 및 함수
    /// </summary>
    public static class GlobalStatic
    {
        public static OpCode[] m_SingleOpcodes = null;
        public static OpCode[] m_MultiOpcodes = null;
        /// <summary>
        /// OpCode 파싱한 뒤 저장
        /// </summary>
        public static void LoadOpcode()
        {
            m_SingleOpcodes = new OpCode[0x100];
            m_MultiOpcodes = new OpCode[0x100];
            
            FieldInfo[] fields = typeof(OpCodes).GetFields();
         
            foreach (FieldInfo field in fields)
            {
                if (field.FieldType == typeof(OpCode))
                {
                    OpCode code1 = (OpCode)field.GetValue(null);
                    ushort num2 = (ushort)code1.Value;
                    if (num2 < 0x100)
                    {
                        m_SingleOpcodes[(int)num2] = code1;
                    }
                    else
                    {
                        if ((num2 & 0xff00) != 0xfe00)
                        {
                            throw new Exception("Invalid OpCode.");
                        }
                        m_MultiOpcodes[num2 & 0xff] = code1;
                    }
                }
            }


            
        }
    }

    public class MyMethodInfo
    {
        Byte[] ILCodes;
        List<ILInstruct> ILInst = new List<ILInstruct>();

        public MyMethodInfo() { }
        public MyMethodInfo(MethodInfo method)
        {
            ILCodes = method.GetMethodBody().GetILAsByteArray();
            ILInstruct ILTemp= new ILInstruct();




        }

    }

    public static class ILCodeReader
    {
        Byte[] ILCode;
        public ILCodeReader(Byte[] ILCode)
        {
            this.ILCode = ILCode;

        }
        public void ILBytetoILCode()
        {
            int index = 0;



        }
        public int BytesTo32Bit(ref int index)
        {
            return (((ILCode[index++] | (ILCode[index++] << 8)) | (ILCode[index++]<<16)) | ILCode[index++] << 24);
        }
        public long BytesTo64Bit(ref int index)
        {
            return (((((((ILCode[index++] | (ILCode[index++] << 8)) | (ILCode[index++] << 0x10)) | (ILCode[index++] << 0x18)) |
                (ILCode[index++] << 0x20))| (ILCode[index++] << 0x28))| (ILCode[index++] << 0x30))| (ILCode[index++] << 0x38));
        }
        public short BytesTo16Bit(ref int index)
        {
            return (short)(ILCode[index++] | (ILCode[index++] << 8));
        }
        public byte ByteTo8Bit(ref int index)
        {
            return ILCode[index++];
        }
    }
}
