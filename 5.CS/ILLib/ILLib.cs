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
        object operand;
        int offset;

        public int Offset
        {
            get { return offset; }
            set { offset = value; }
        }

        public OpCode Opcode
        {
            get { return opcode; }
            set { opcode = value; }
        }
        public object Operand
        {
            get { return operand; }
            set { operand = value; }
        }

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

        //public MyMethodInfo() { }
        public MyMethodInfo(MethodInfo method)
        {
            ILCodes = method.GetMethodBody().GetILAsByteArray();
            ILInstruct ILTemp= new ILInstruct();

        }

    }

    public class ILCodeReader
    {
        Module m_Module;
        Byte[] ILCode;
        public List<ILInstruct> m_ILInstructs;

        public ILCodeReader(Module module, Byte[] ILCode)
        {
            this.m_Module = module;
            this.ILCode = ILCode;
            ILBytestoILCode(module, ILCode);
        }
        public void ILBytestoILCode(Module module, Byte[] ILCode)
        {
            int operandvalue = 0;
            int index = 0;
            m_ILInstructs = new List<ILInstruct>();
            //ilcode 구성 : 첫 바이트는 opcode 종류.
            //              opcode.operandtype에 따라 다음 오퍼랜드 길이가 정해진다.

            ILInstruct ilTemp;
            for (index = 0; index < ILCode.Length - 1; )
            {
                ilTemp = new ILInstruct();
                operandvalue = 0;

                OpCode opcode = OpCodes.Nop;
                ushort value = ILCode[index++];

                // ilcode가 일 경우
                if (value != 0xfe)
                {
                    opcode = GlobalStatic.m_SingleOpcodes[(int)value];
                }
                else
                {
                    value = ILCode[index++];
                    opcode = GlobalStatic.m_MultiOpcodes[(int)value];
                    value = (ushort)(value | 0xfe00);
                }
                ilTemp.Opcode = opcode;
                ilTemp.Operand = 0;
                ilTemp.Offset = index - 1;
                //string 빼고 다 확인 필요
                switch(opcode.OperandType)
                {
                    case OperandType.InlineBrTarget:  //점프 주소가 와야할듯 해당 명령어 확인필요
                        operandvalue = BytesTo32Bit(ref index);
                        //ilTemp.Operand = module.ResolveString(operandvalue);
                        break;
                    case OperandType.InlineField:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.InlineI:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.InlineI8:
                        ilTemp.Operand = BytesTo64Bit(ref index);
                        break;
                    case OperandType.InlineMethod:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = module.ResolveMethod(operandvalue);
                        break;
                    case OperandType.InlineNone:
                        ilTemp.Operand = null;
                        break;
                    //case OperandType.InlinePhi: break;
                    case OperandType.InlineR:   //IEEE floating point number - double
                        ilTemp.Operand = BytesToDouble(ref index);
                        break;
                    case OperandType.InlineSig:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = module.ResolveSignature(operandvalue);
                        break;
                    case OperandType.InlineString:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = module.ResolveString(operandvalue);
                        break;
                    case OperandType.InlineSwitch:
                        ilTemp.Operand = BytesTo32Bit(ref index);
                        break;
                    case OperandType.InlineTok:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = module.ResolveSignature(operandvalue);
                        break;
                    case OperandType.InlineType:
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.InlineVar:
                        operandvalue = BytesTo16Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.ShortInlineBrTarget:
                        operandvalue = ByteTo8Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.ShortInlineI: 
                        operandvalue = ByteTo8Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.ShortInlineR: 
                        operandvalue = BytesTo32Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    case OperandType.ShortInlineVar:
                        operandvalue = ByteTo8Bit(ref index);
                        ilTemp.Operand = operandvalue;
                        break;
                    default: break;
                }
                m_ILInstructs.Add(ilTemp);

            }

        }

        //명령어 변환용 비트 연산
        public int BytesTo32Bit(ref int index)
        {
            return (((ILCode[index++] | (ILCode[index++] << 8)) | (ILCode[index++]<<16)) | ILCode[index++] << 24);
        }
        public ulong BytesTo64Bit(ref int index)
        {
            return (ulong)(((((((ILCode[index++] | (ILCode[index++] << 8)) | (ILCode[index++] << 0x10)) | (ILCode[index++] << 0x18)) |
                (ILCode[index++] << 0x20))| (ILCode[index++] << 0x28))| (ILCode[index++] << 0x30))| (ILCode[index++] << 0x38));
        }
        public double BytesToDouble(ref int index)
        {
            return (double)(((((((ILCode[index++] | (ILCode[index++] << 8)) | (ILCode[index++] << 0x10)) | (ILCode[index++] << 0x18)) |
                (ILCode[index++] << 0x20)) | (ILCode[index++] << 0x28)) | (ILCode[index++] << 0x30)) | (ILCode[index++] << 0x38));
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
