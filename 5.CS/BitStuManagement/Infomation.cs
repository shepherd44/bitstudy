using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Windows.Data;

namespace BitStuManagement
{
    public class Human : INotifyPropertyChanged//, IValueConverter
    {
        protected string m_HumanCode;
        protected string m_Name;
        protected int m_Age;
        protected string m_BirthDay;

        #region Human Property
        string Name
        {
            get { return m_Name; }
            set 
            {
                m_Name = value;
                FirePropertyChanged("Name");
            }
        }
        int Age
        {
            get { return m_Age; }
            set
            {
                m_Age = value;
                FirePropertyChanged("Age");
            }
        }
        string BirthDay
        {
            get { return m_BirthDay; }
            set
            {
                m_BirthDay = value;
                FirePropertyChanged("BirthDay");
            }
        }
        #endregion
        #region INotifyProperyChanged Members
        public event PropertyChangedEventHandler PropertyChanged;
        protected void FirePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion
        #region IValueConverter
        //public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        //{
        //    throw new NotImplementedException();
        //}

        //public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        //{
        //    throw new NotImplementedException();
        //}
        #endregion
    }
    public class StudentInfo: Human, INotifyPropertyChanged
    {
        private List<LectureInfo> m_ListLecture = new List<LectureInfo>();

        #region StudentInfo method
        public void AddLecture(LectureInfo lecture)
        {
                m_ListLecture.Add(lecture);
        }
        public void RemoveLecture(int index)
        {
            m_ListLecture.RemoveAt(index);
        }
        public LectureInfo GetLecture(int index)
        {
            return m_ListLecture.ElementAt(index);
        }
        #endregion
        #region StudentInfo Property
        public string StudentCode
        {
            get { return m_HumanCode; }
            set
            {
                m_HumanCode = "S"+value;
                FirePropertyChanged(m_HumanCode);
            }
        }

        #endregion

    }
    public class InstructorInfo : Human, INotifyPropertyChanged
    {
        #region InstructorInfo Property
        public string InstructorCode
        {
            get { return m_HumanCode; }
            set
            {
                m_HumanCode = "I"+value;
                FirePropertyChanged(m_HumanCode);
            }
        }

        #endregion
    }
    public class ManagerInfo : Human, INotifyPropertyChanged
    {
        #region ManagerInfo Property
        public string ManagerCode
        {
            get { return m_HumanCode; }
            set
            {
                m_HumanCode = "M"+value;
                FirePropertyChanged(m_HumanCode);
            }
        }

        #endregion
    }
    public class Attendence { }
    public class LectureInfo
    {
        private string m_LectureName;
        private string m_LectureCode;
        private string m_LectureRoom;
        private int m_MaxStudentNum;
        private int m_CurStudentNum;
        private InstructorInfo m_Instructor;
        private ManagerInfo m_Manager;
        private List<StudentInfo> m_StudentList = new List<StudentInfo>();

        #region LectureInfo method
        public void AddStudent(StudentInfo stu)
        {
            if (m_StudentList.Count <= m_MaxStudentNum)
                m_StudentList.Add(stu);
        }
        public void RemoveStudent(int index)
        {
            m_StudentList.RemoveAt(index);
        }
        public StudentInfo GetStudent(int index)
        {
            return m_StudentList.ElementAt(index);
        }
        #endregion
        #region LectureInfo Property
        public string LectureName
        {
            get { return m_LectureName; }
            set { m_LectureName = value; }
        }
        public string LectureCode
        {
            get { return m_LectureCode; }
            set { m_LectureCode = "L"+value; }
        }
        public string LectureRoom
        {
            get { return m_LectureRoom; }
            set { m_LectureRoom = value; }
        }

        public int MaxStudentNum
        {
            get { return m_MaxStudentNum; }
            set { m_MaxStudentNum = value; }
        }

        public int CurStudentNum
        {
            get { return m_CurStudentNum; }
            set { m_CurStudentNum = value; }
        }
        #endregion
    }
}
