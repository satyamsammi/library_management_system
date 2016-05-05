#include <bits/stdc++.h>
#include <ctime>

using namespace std;

struct Date
{
    int d, m, y;
};

bool roll_check(string);
bool isbn_check(string);
bool string_check(string);
int getDifference(Date dt1, Date dt2);
string get_branch(string);

struct issue_return
{
    string isbn;
    int bid;
    tm *date;
};

struct returns
{
    string roll_no,isbn;
    int bid,fine;
    tm *idate,*rdate;
};

struct stu
{
    string name, roll_no,branch;
    int issued,fine,tot_returns;
    issue_return *bk[5];
};

struct book
{
    string bname,publication,isbn;
    vector<string> author;
    int tot,in_inventory,max_bid,authors,category;
    set<int> ids;
};

class books
{
    public:
    int type_books,tot_books,issued_books;
    vector<book>::iterator it1;
    vector<book> bk;
    set<int>::iterator it2;
    string isb,bi;
    void add_book();
    books();
    void delete_book();
    void see_book();
    void search_pub();
    void view_all();
    void view_authors();
    void view_by_cat();
};

books::books()
{
    type_books=tot_books=issued_books=0;
}

class students
{
    public:
    int num;
    string roll,nam;
    vector<stu> student;
    vector<stu>::iterator it;
    void add_student();
    void delete_student();
    students();
    void issue_book(books &bks);
    void return_book(books &bks);
    void view_issues();
    void search_book(books &bks);
    void pay_fine();
    void view_all();
    void view_return_history();
    vector<returns> ret;
    vector<returns>::iterator it3;
};

students::students()
{
    num=0;
}
const int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};

int countLeapYears(Date d)
{
    int years = d.y;
    if (d.m <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
    long int n1 = dt1.y*365 + dt1.d;
    for (int i=0; i<dt1.m - 1; i++)
        n1 += monthDays[i];
    n1 += countLeapYears(dt1);
    long int n2 = dt2.y*365 + dt2.d;
    for (int i=0; i<dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
    return (n2 - n1);
}

bool roll_check(string a)
{
    int i=a.find('/'),j,l=a.length();
    if(i==-1)
    {
        cout << "Not proper format for roll no., roll no. should be in format <ints<=3>/<dept_code>/<2xint>"<<endl;
        return false;
    }
    else
    {
        for(j=0;j<i;j++)
        {
            if(a[j]<'0'||a[j]>'9')
            {
                cout << "Not proper format for roll no., roll no. should be in format <ints<=3>/<dept_code>/<2xint>"<<endl;
                return false;
            }
        }
        j=a.find('/',i+1);
        if(j==-1)
        {
            cout << "Not proper format for roll no., roll no. should be in format <ints<=3>/<dept_code>/<2xint>"<<endl;
            return false;
        }
        else
        {
            if(l-j!=3)
            {
                cout << "Not proper format for roll no., roll no. should be in format <ints<=3>/<dept_code>/<2xint>"<<endl;
                return false;
            }
            for(++i;i<j;i++)
            {
                if(a[i]<'A'||a[i]>'Z')
                {
                    cout << "Not proper format for roll no., roll no. should be in format <ints<=3>/<dept_code>/<2xint>"<<endl;
                    return false;
                }
            }
            for(++j;j<l;j++)
            {
                if(a[j]<'0'||a[j]>'9')
                {
                   cout << "Not proper format for roll no., roll no. should be in format <ints<=3>/<dept_code>/<2xint>"<<endl;
                   return false;
                }
            }
            if(a[l-2]!='1'||(a[l-1]<'1')||(a[l-1]>'5'))
            {
                cout << "Year of admission is not valid\n";
                return false;
            }
        }
    }
    return true;
}

bool isbn_check(string a)
{
    int i,l=a.length();
    if(l!=10&&l!=13)
    {
        cout << "Not proper format for ISBN, can only contain integers 10 or 13\n"<<endl;
        return false;
    }
    else
    {
        for(i=0;i<l;i++)
        {
            if(a[i]<'0'||a[i]>'9')
            {
                cout << "Not proper format for ISBN, can only contain integers 10 or 13\n"<<endl;
                return false;
            }
        }
    }
    return true;
}

bool string_check(string a)
{
    int i,l=a.length();
    for(i=0;i<l;i++)
    {
        if((a[i]>='A'&&a[i]<='Z')||(a[i]>='a'&&a[i]<='z')||(a[i]==' ')||(a[i]=='.'))
        continue;
        else
        {
            cout << "Specified field can only contain alphabets or blank-space or dot<.>\n";
            return false;
        }
    }
    return true;
}

string get_branch(string a)
{
    int i,j;
    //l=a.length();
    i=a.find('/');
    j=a.find('/',i+1);
    string b=a.substr(i+1,j-i-1);
    if(b.compare("CO")==0)
    return "COE";
    else if(b.compare("EC")==0)
    return "ECE";
    else if(b.compare("IT")==0)
    return "IT";
    else if(b.compare("MP")==0)
    return "MPAE";
    else if(b.compare("IC")==0)
    return "ICE";
    else if(b.compare("BT")==0)
    return "BT";
    else
    {
        cout << "Not a valid branch code in the roll no.\n";
        return "no";
    }
}

void students::add_student()
{
    int j;
    g1:
    cout << "Enter student roll no."<<endl;
    cin >> roll;
    j=roll_check(roll);
    if(j==0)
    return;
    string a=get_branch(roll);
    if(a.compare("no")==0)
    return;
    for(it=student.begin(),j=0;it!=student.end();it++)
    {
        if(roll.compare((*it).roll_no)==0)
        {
            cout << "This roll no. already exists, please try again\n";
            j=1;
            return;
            break;
        }
    }
    if(j)
    {
        goto g1;
    }
    else
    {
        cout << "Enter Student name\n";
        cin.clear();
        while (cin.get() != '\n')
        {
            continue;
        }
        getline(cin,nam);
        int al=string_check(nam);
        if(!al)
        {
            return;
        }
        stu a;
        a.branch=get_branch(roll);
        a.name=nam;
        a.roll_no=roll;
        a.issued=a.fine=a.tot_returns=0;
        a.bk[0]=a.bk[1]=a.bk[2]=a.bk[3]=a.bk[4]=NULL;
        student.push_back(a);
        num++;
        cout << "Student added succesfully\n";
    }
    return;
}

void students::delete_student()
{
    cout << "Enter the roll no. of the student you want to delete\n";
    cin >> roll;
    int j;
    stu a;
    for(it=student.begin(),j=0;it!=student.end();it++)
    {
        if(roll.compare((*it).roll_no)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        a=(*it);
        if(a.issued==0&&a.fine==0)
        {
            cout << "Student doesn not have any books issued and has been successfully removed from the database\n";
            student.erase(it);
            num--;
        }
        else if(a.fine!=0)
        {
            cout << "Student has Rs. "<< a.fine <<" to be payed as fine,he should first pay the fine to be removed\n";
        }
        else
        {
            cout <<"Student has some books issued, he should first return those\n";
        }
    }
    else
    {
        cout << "No student with the given roll no. is present in the database\n";
    }
    return ;
}

int abs(int a)
{
    if(a<0)
    return -1*a;
    return a;
}

void books::add_book()
{
    cout<< "Enter the ISBN for the book you want to enter\n";
    cin >> isb;
    int i,j,k;
    j=isbn_check(isb);
    if(j==0)
    return;
    string a;
    for(it1=bk.begin(),j=0;it1!=bk.end();it1++)
    {
        if(isb.compare((*it1).isbn)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout << "How many books are to be added for this ISBN\n";
        cin >> i;
        for(k=1;k<=i;k++)
        (*it1).ids.insert((*it1).max_bid+k);
        cout << "books for the provided ISBN with bid from "<<(*it1).max_bid+1<<" to bid "<<(*it1).max_bid+i<< " have been added\n";
        (*it1).tot+=i;
        (*it1).max_bid+=i;
        (*it1).in_inventory+=i;
        cout << "Books added succesfully\n\n";
    }
    else
    {
        cout << "Please provide the following details\nNumber of authors\n";
        int l;
        cin >>l;
        l=abs(l);
        book b;
        cin.clear();
        while (cin.get() != '\n')
        {
            continue;
        }
        b.authors=l;
        while(l--)
        {
            cout << "Enter author name\n";
            getline(cin,a);bool al=string_check(a);
            if(!al)
                return;
            b.author.push_back(a);
        }
        g2:
        cout <<"Please enter category of the book\n1.) Literature\n2.) Textbook\n3.) General awareness\n4.) Misc.\n";
        int cat;
        cin >> cat;
        if(cat<1||cat>4)
        {
            cout <<"Not a valid category,try again\n";
            goto g2;
        }
        b.category=cat;
        cout << "Please enter the name of the publication\n";
        cin.clear();
        while(cin.get()!='\n')
        continue;
        getline(cin,a);
        bool al=string_check(a);
        if(!al)
        return;
        b.publication=a;
        cout << "Please enter the title of the book\n";
        getline(cin,a);
        al=string_check(a);
        if(!al)
        return;
        b.bname=a;
        b.isbn = isb;
        cout << "How many books are to be added for this ISBN\n";
        cin >> i;
        for(int k=1;k<=i;k++)
        b.ids.insert(k);
        b.tot=b.in_inventory=b.max_bid=i;
        bk.push_back(b);
        cout << "Books successfully added\n\n";
    }
    return;
}

void books::delete_book()
{
    int i,j;
    cout << "Enter the ISBN of the textbook you want to delete\n";
    cin >> isb;
    string a;
    for(it1=bk.begin(),j=0;it1!=bk.end();it1++)
    {
        if(isb.compare((*it1).isbn)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout << "Enter bid of the textbook you want to delete\n";
        cin >> i;
        it2 = (*it1).ids.find(i);
        if(it2!=(*it1).ids.end())
        {
            (*it1).ids.erase((*it2));
            cout << "book has been successfully deleted\n";
            (*it1).tot--;
            (*it1).in_inventory--;
        }
        else
        {
            cout << "The bid for given ISBN is not in the library and thus can't be deleted\n";
        }
    }
    else
    {
        cout << "Provided ISBN does not exist, please try again\n";
    }
    return;
}

void students::issue_book(books &bks)
{
    cout <<"Enter the roll no. of the student who wants to issue a book\n";
    string a;
    cin >> a;
    int i,j,k;
    for(it=student.begin(),j=0;it!=student.end();it++)
    {
        if(a.compare((*it).roll_no)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        if((*it).issued==5)
        {
            cout << "Student has already issued 5 books, no more books can be issued\n";
            return;
        }
        cout << "Enter the ISBN of the textbook\n";
        cin >> a;
        for(bks.it1=bks.bk.begin(),i=0;bks.it1!=bks.bk.end();bks.it1++)
        {
            if(a.compare((*bks.it1).isbn)==0)
            {
                i=1;
                break;
            }
        }
        if(i)
        {
            cout << "Enter the bid of the book\n";
            cin >> i;
            time_t now = time(0);
            bks.it2=(*bks.it1).ids.find(i);
            if(bks.it2!=(*bks.it1).ids.end())
            {
                (*bks.it1).in_inventory--;
                (*bks.it1).ids.erase(i);
                (*it).issued++;
                k=0;
                while((*it).bk[k]!=NULL&&k<5)
                k++;
                (*it).bk[k] = new issue_return;
                (*it).bk[k]->date = localtime(&now);
                (*it).bk[k]->isbn = (*bks.it1).isbn;
                (*it).bk[k]->bid = i;
                cout << "Book succesfully issued on "<<(*it).bk[k]->date->tm_mday<<"-"<<(*it).bk[k]->date->tm_mon+1<<"-"<<(*it).bk[k]->date->tm_year+1900<<endl;
            }
            else
            cout << "Book of given bid is not in the library, thus can't be issued to the student\n";
        }
        else
        {
            cout << "No book with given ISBN is present in the library\n";
            return;
        }
    }
    else
    {
        cout << "No student with this roll no. exists\n";
    }
    return;
}

void students::return_book(books &bks)
{
    int i,j,k;
    string a;
    cout << "Enter the roll no. of the student returning the book\n";
    cin>> a;
    for(it=student.begin(),j=0;it!=student.end();it++)
    {
        if(a.compare((*it).roll_no)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        if((*it).issued==0)
        {
            cout << "This student has no books issued\n";
            return;
        }
        k=0;i=0;
        while(k<5)
        {
            if((*it).bk[k]!=NULL)
            {
                i++;
                cout <<i<<".) ISBN: "<<(*it).bk[k]->isbn<<",    Book id.: "<<(*it).bk[k]->bid<<endl;
            }
            k++;
        }
        g1:
        cout << "Enter the index number of the book student is returning\n";
        cin>> j;
        if(j>i||j<=0)
        {
            cout << "Invalid entry, please try again\n";
            goto g1;
        }
        k=0;i=0;
        while(k<5)
        {
            if((*it).bk[k]!=NULL)
            {
                i++;
                if(i==j)
                {
                    a=(*it).bk[k]->isbn;
                    int l;
                    for(bks.it1=bks.bk.begin(),l=0;bks.it1!=bks.bk.end();bks.it1++)
                    {
                        if(a.compare((*bks.it1).isbn)==0)
                        {
                            l=1;
                            break;
                        }
                    }
                    if(l)
                    {
                        time_t now=time(0);
                        returns b;
                        b.roll_no = (*it).roll_no;
                        b.bid = (*it).bk[k]->bid;
                        b.isbn = (*bks.it1).isbn;
                        b.rdate = localtime(&now);
                        b.idate = (*it).bk[k]->date;
                        Date dt1,dt2;
                        cout <<(*it).bk[k]->date->tm_mday<<" "<<(*it).bk[k]->date->tm_mon+1<<" "<<(*it).bk[k]->date->tm_year+1900<<endl;
                        dt1.d = (*it).bk[k]->date->tm_mday;
                        dt1.m = (*it).bk[k]->date->tm_mon+1;
                        dt1.y = (*it).bk[k]->date->tm_year+1900;
                        dt2.d = b.rdate->tm_mday;
                        dt2.m = b.rdate->tm_mon+1;
                        dt2.y = b.rdate->tm_year+1900;
                        int al=getDifference(dt1,dt2);
                        if((*bks.it1).category==2)
                        {
                            if(al>20)
                            {
                                b.fine = (al-20)*5;
                                (*it).fine+=(al-20)*5;
                                cout << "Book has been returned succesfully, with a fine of "<< (al-20)*5<<endl;
                                cout<<"dated: "<<dt2.d<<"-"<<dt2.m<<"-"<<dt2.y<<endl;
                            }
                            else
                            {
                                b.fine=0;
                                cout << "Book has been returned succesfully without any fine"<<endl;
                                cout<<"dated: "<<dt2.d<<"-"<<dt2.m<<"-"<<dt2.y<<endl;
                            }
                        }
                        else{
                        if(al>14)
                        {
                            b.fine=(al-14)*5;
                            (*it).fine+=(al-14)*5;
                            cout << "Book has been returned succesfully, with a fine of "<< (al-14)*5<<endl;
                            cout<<"dated: "<<dt2.d<<"-"<<dt2.m<<"-"<<dt2.y<<endl;
                        }
                        else
                        {
                            b.fine = 0;
                            cout << "Book has been returned succesfully without any fine"<<endl;
                            cout<<"dated: "<<dt2.d<<"-"<<dt2.m<<"-"<<dt2.y<<endl;
                        }
                        }
                        i=(*it).bk[k]->bid;
                        (*bks.it1).ids.insert(i);
                        (*bks.it1).in_inventory++;
                        (*it).bk[k]->date=NULL;
                        delete (*it).bk[k];
                        (*it).issued--;
                        (*it).bk[k]=NULL;
                        (*it).tot_returns++;
                        ret.push_back(b);
                        cout <<"Exit\n";
                    }
                }
            }
            k++;
        }
    }
    else
    cout << "Invalid roll no.\n";
    return;
}

void students::view_issues()
{
    int i,j,k;
    string a;
    cout << "Enter the roll no. of the student you want to view\n";
    cin>> a;
    for(it=student.begin(),j=0;it!=student.end();it++)
    {
        if(a.compare((*it).roll_no)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout << "Name: "<<(*it).name<<",    Books issued: "<<(*it).issued<<",    fine: "<<(*it).fine<<endl;
        k=0;i=0;
        while(k<5)
        {
            if((*it).bk[k]!=NULL)
            {
                i++;
                cout <<i<<".) ISBN: "<<(*it).bk[k]->isbn<<",    Book id.: "<<(*it).bk[k]->bid<<endl;
                cout<<"dated: "<<(*it).bk[k]->date->tm_mday<<"-"<<(*it).bk[k]->date->tm_mon+1<<"-"<<(*it).bk[k]->date->tm_year+1900<<endl;
            }
            k++;
        }
    }
    else
    {
        cout << "Invalid roll no.\n";
    }
    return;
}

void students::search_book(books &bks)
{
    string a;
    int i,j,k,b;
    cout <<"Enter the book ISBN code\n";
    cin >> a;
    for(bks.it1=bks.bk.begin(),j=0;bks.it1!=bks.bk.end();bks.it1++)
    {
        if(a.compare((*bks.it1).isbn)==0)
        {
            j=1;
            break;
        }
    }
    if(j==0)
    {
        cout << "ISBN code didn't match any textbook\n";
        return;
    }
    else
    {
        cout <<"Enter the book id\n";
        cin >> b;
        bks.it2 = (*bks.it1).ids.find(b);
        if(bks.it2==(*bks.it1).ids.end())
        {
            for(it=student.begin(),k=0;it!=student.end()&&k==0;it++)
            {
                i=0;
                while(i<5)
                {
                    if((*it).bk[i]!=NULL)
                    {
                        if((*it).bk[i]->isbn.compare(a)==0&&(*it).bk[i]->bid==b)
                        {
                            k=1;
                            cout << "The book has been to issued to-  "<<(*it).name<<" "<<(*it).roll_no<<endl;
                        }
                    }
                    i++;
                }
            }
            if(k==0)
            {
                cout << "The book is not part of the library\n";
            }
        }
        else
        {
            cout <<"Book is in the library\n";
        }
    }
    return;
}

void students::pay_fine()
{
    int i,j;
    string a;
    cout << "Enter the roll no. of the student you want to view\n";
    cin>> a;
    for(it=student.begin(),j=0;it!=student.end();it++)
    {
        if(a.compare((*it).roll_no)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout << "Student has a fine of Rs. "<<(*it).fine<<" due against him, enter the amount he wishes to pay\n";
        cin >> i;
        if(i>(*it).fine)
        {
            cout << "Amount entered is greater than fine due, please try again\n";
            return;
        }
        else if(i<0)
        {
            cout << "Negative values not allowed\n";
            return;
        }
        else
        (*it).fine-=i;
    }
    else
    {
        cout << "Roll no. entered is not registered\n";
        return;
    }
}

void books::see_book()
{
    string a;
    int j;
    cout <<"Enter the book ISBN code\n";
    cin >> a;
    for(it1=bk.begin(),j=0;it1!=bk.end();it1++)
    {
        if(a.compare((*it1).isbn)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout<< "Following are the available bids in the library\n";
        for(it2=(*it1).ids.begin();it2!=(*it1).ids.end();it2++)
        {
            cout <<(*it2)<<endl;
        }
    }
    else
    cout <<"Invalid ISBN\n";
    return;
}

void books::search_pub()
{
    string a,b;
    int j;
    cin.clear();
    while(cin.get()!='\n')
    continue;
    cout <<"Enter the book's publication name\n";
    getline(cin,a);
    cout << "Enter the book's title\n";
    getline(cin,b);
    for(it1=bk.begin(),j=0;it1!=bk.end();it1++)
    {
        if((a.compare((*it1).publication)==0)&&(b.compare((*it1).bname)==0))
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout << "Following is the book you are searching for\n";
        cout <<endl<<"ISBN: "<<(*it1).isbn<<",    Publication: "<<(*it1).publication<<",    title: "<<(*it1).bname<<endl;
        cout << "Available copies in the library: "<<(*it1).in_inventory<<endl;
    }
    else
    {
        cout<< "No book found with a combination of title and publication provided\n";
        return ;
    }
}

void students::view_all()
{
    cout << "Following are the students registered\n";
    for(it=student.begin();it!=student.end();it++)
    {
        cout << "Roll no.: "<<(*it).roll_no<<",    Name: "<<(*it).name<<",    Branch: "<<(*it).branch<<endl;
        cout << "Books issued: "<<(*it).issued<<endl<<endl;
    }
    cout << endl;
}

void books::view_all()
{
    cout <<"Following are the books in the library\n";
    for(it1=bk.begin();it1!=bk.end();it1++)
    {
        cout <<"ISBN: "<<(*it1).isbn<<",    Publication: "<<(*it1).publication<<",    title: "<<(*it1).bname<<",    category: ";
        if((*it1).category==1)
        cout << "Literature\n";
        else if((*it1).category==2)
        cout << "Textbook\n";
        else if((*it1).category==3)
        cout << "General awareness\n";
        else
        cout << "Misc.\n";
        cout << "Available copies in the library: "<<(*it1).in_inventory<<endl<<endl;
    }
    cout << endl;
}

void books::view_authors()
{
    string a;
    int j;
    cout <<"Enter the book ISBN code\n";
    cin >> a;
    for(it1=bk.begin(),j=0;it1!=bk.end();it1++)
    {
        if(a.compare((*it1).isbn)==0)
        {
            j=1;
            break;
        }
    }
    if(j)
    {
        cout << "Following are the authors of the book\n";
        int i=(*it1).authors;
        while(i--)
        {
            cout << (*it1).author[i]<<endl;
        }
        cout << endl;
    }
    else
    {
        cout << "No book found with the provided ISBN\n";
    }
    return ;
}

void students::view_return_history()
{
    int j;
    string a;
    cout << "Enter the roll no. of the student you want to view\n";
    cin>> a;
    int i=0;
        for(it3=ret.begin();it3!=ret.end();it3++)
        {
            if((*it3).roll_no.compare(a)==0)
            {
                i++;
                if(i==1)
                {
                    cout << "Roll no.: "<<(*it3).roll_no <<endl;
                }
                cout << "ISBN: "<<(*it3).isbn<<",   bid: "<<(*it3).bid<<",  fine: "<<(*it3).fine<<endl;
                cout << "Issued on: "<<(*it3).idate->tm_mday<<"-"<<(*it3).idate->tm_mon<<"-"<<(*it3).idate->tm_year<<endl;
                cout << "Returned on: "<<(*it3).rdate->tm_mday<<"-"<<(*it3).rdate->tm_mon<<"-"<<(*it3).rdate->tm_year<<endl<<endl;
            }
        }
    return ;
}

void write_Student_result(students s,books b)
{
    ofstream file1;
    file1.open("student");
    int count=s.num;
    file1<<count<<endl;
    for(int i=0;i<count;i++)
    {
        file1<<s.student[i].name<<endl;
        file1<<s.student[i].roll_no<<endl;
        file1<<s.student[i].branch<<endl;
        file1<<s.student[i].issued<<endl;
        file1<<s.student[i].fine<<endl;
        file1<<s.student[i].tot_returns<<endl;
        for(int j=0;j<5;j++)
        {
            if(s.student[i].bk[j]!=NULL)
            {
                file1<<s.student[i].bk[j]->isbn<<endl;
                file1<<s.student[i].bk[j]->bid<<endl;
                file1<<s.student[i].bk[j]->date->tm_mday<<endl;
                file1<<s.student[i].bk[j]->date->tm_mon<<endl;
                file1<<s.student[i].bk[j]->date->tm_year<<endl;
            }
        }
    }
    ofstream file2;
    file2.open("books");
    file2<<b.bk.size()<<endl;
    //cout<<b.bk.size();
    for(int i=0;i<b.bk.size();i++)
    {
        file2<<b.bk[i].bname<<endl;
        file2<<b.bk[i].authors<<endl;
        for(int j=0;j<b.bk[i].author.size();j++)
        {
            file2<<b.bk[i].author[j]<<endl;
        }
        file2<<b.bk[i].category<<endl;
        file2<<b.bk[i].publication<<endl;
        file2<<b.bk[i].isbn<<endl;
        file2<<b.bk[i].tot<<endl;
        file2<<b.bk[i].in_inventory<<endl;
        file2<<b.bk[i].max_bid<<endl;

       for(b.it2=b.bk[i].ids.begin();b.it2!=b.bk[i].ids.end();b.it2++)
        {
            file2<<*(b.it2)<<endl;
        }


    }
    file1.close();
    file2.close();
    file2.open("ret");
    file2<<s.ret.size()<<endl;
    for(int j=0;j<s.ret.size();j++)
    {
        file2<<s.ret[j].roll_no<<endl;
        file2<<s.ret[j].isbn<<endl;
        file2<<s.ret[j].bid<<endl;
        file2<<s.ret[j].fine<<endl;
        file2<<s.ret[j].idate->tm_mday<<endl;
        file2<<s.ret[j].idate->tm_mon<<endl;
        file2<<s.ret[j].idate->tm_year<<endl;
        file2<<s.ret[j].rdate->tm_mday<<endl;
        file2<<s.ret[j].rdate->tm_mon<<endl;
        file2<<s.ret[j].rdate->tm_year<<endl;
    }
    file2.close();
}

void read_from_records(books &b,students &a)
{
    ifstream file1;
    file1.open("books",ios::out);
    int count=0;
    file1>>count;
    b.tot_books=0;
    for(int i=0;i<count;i++)
    {
        book book1;
       // string bname1,publication1,isbn1;
        string local_names;
        int local_num;
        //vector<string> author1;
        //int tot1,in_inventory1,max_bid1,authors1;
        set<int> ids;
        //getline(file1,book1.bname);
        file1.clear();
        while(file1.get()!='\n')
            continue;
        getline(file1,book1.bname);
        //book1.bname=bname1;
        file1>>book1.authors;
        file1.clear();
        while(file1.get()!='\n')
        continue;
        getline(file1,local_names);
        book1.author.push_back(local_names);
        //book1.authors=authors1;
        for(int j=1;j<book1.authors;j++)
        {
            getline(file1,local_names);
            //file1>>local_names;
            book1.author.push_back(local_names);
        }
        file1>>book1.category;
        file1.clear();
        while(file1.get()!='\n')
        continue;
        getline(file1,book1.publication);
        getline(file1,book1.isbn);
        file1>>book1.tot;
        file1>>book1.in_inventory;
        file1>>book1.max_bid;
        for(int j=0;j<book1.in_inventory;j++)
        {
            file1>>local_num;
            book1.ids.insert(local_num);
        }
        b.bk.push_back(book1);
        b.tot_books++;
    }
    file1.close();
    file1.open("student",ios::out);
    string local;
    int i;
    count =0;
    file1>>count;
    file1.clear();
    while(file1.get()!='\n')
        continue;
    for(i=0;i<count;i++)
    {
        stu student1;
        getline(file1,student1.name);
        getline(file1,student1.roll_no);
        getline(file1,student1.branch);
        file1>>student1.issued;
               file1>>student1.fine;
               file1>>student1.tot_returns;
        int j;

        for(j=0;j<student1.issued;j++)
        {

            student1.bk[j]=new issue_return;
            file1.clear();
            while(file1.get()!='\n')
                continue;

    //cout << 2;
            getline(file1,student1.bk[j]->isbn);
      //      cout <<2;
            file1>>student1.bk[j]->bid;
            time_t now=time(0);
            student1.bk[j]->date = new tm;
            file1>>student1.bk[j]->date->tm_mday;
            file1>>student1.bk[j]->date->tm_mon;
            file1>>student1.bk[j]->date->tm_year;
        }
        for(;j<5;j++)
        {
            student1.bk[j]=NULL;
        }
        a.student.push_back(student1);
        file1.clear();
        while(file1.get()!='\n')
        continue;
    }
    a.num=count;
    file1.close();
    file1.open("ret",ios::out);
    file1>>i;
    file1.clear();
    while(file1.get()!='\n')
        continue;
    returns c;
    c.idate =new tm;
    c.rdate = new tm;
    while(i--)
    {
        getline(file1,c.roll_no);
        getline(file1,c.isbn);
        file1>>c.bid;
        file1>>c.fine;
        file1>>c.idate->tm_mday;
        file1>>c.idate->tm_mon;
        file1>>c.idate->tm_year;
        file1>>c.rdate->tm_mday;
        file1>>c.rdate->tm_mon;
        file1>>c.rdate->tm_year;
        while(file1.get()!='\n')
        continue;
        a.ret.push_back(c);
    }
    file1.close();
}

void books::view_by_cat()
{
    g3:
    cout <<"Please enter category of the book\n1.) Literature\n2.) Textbook\n3.) General awareness\n4.) Misc.\n";
    int i;
    cin >> i;
    if(i<1||i>4)
    {
        cout <<"Not a valid category,try again\n";
        goto g3;
    }
    for(it1=bk.begin();it1!=bk.end();it1++)
    {
        if((*it1).category==i)
        {
            cout <<"ISBN: "<<(*it1).isbn<<",    Publication: "<<(*it1).publication<<",    title: "<<(*it1).bname<<endl;
            cout << "Available copies in the library: "<<(*it1).in_inventory<<endl<<endl;
        }
    }
    cout << endl;
}

int main()
{
    students stud;
    books bks;
    int i;
    read_from_records(bks,stud);
    cout << "Enter your choice\n0.) Exit\n1.) Create a student\n2.) Delete a student\n";
    cout <<"3.) Add books to library\n4.) Discard books in library\n5.) Issue book to a student\n";
    cout << "6.) Return a book to the library\n7.) See a student's profile\n8.) Search a book\n9.) Deduct fine amount of student\n";
    cout <<"10.) See available bids for some ISBN\n11.) Search book with publication and title\n12.) View all students\n";
    cout << "13.) View all books in the library\n14.) View return history of a student\n15.) View authors of a bookt\n";
    cout << "16.) View books sorted by category\n";
    cin >> i;
    while(true){
    switch(i)
    {
        case 1: stud.add_student();
                write_Student_result(stud,bks);
                break;
        case 2: stud.delete_student();
                write_Student_result(stud,bks);
                break;
        case 3: bks.add_book();
        write_Student_result(stud,bks);
                break;
        case 4: bks.delete_book();
        write_Student_result(stud,bks);
        break;
        case 5: stud.issue_book(bks);
        write_Student_result(stud,bks);
        break;
        case 6: stud.return_book(bks);
        write_Student_result(stud,bks);
        break;
        case 7: stud.view_issues();
        break;
        case 8: stud.search_book(bks);
        break;
        case 9: stud.pay_fine();
        write_Student_result(stud,bks);
        break;
        case 10: bks.see_book();
        break;
        case 11: bks.search_pub();
        break;
        case 12: stud.view_all();
        break;
        case 13: bks.view_all();
        break;
        case 14: stud.view_return_history();
        break;
        case 15: bks.view_authors();
        break;
        case 16: bks.view_by_cat();
        break;
        case 0: write_Student_result(stud,bks);
        exit(0);
        break;
        default: cout << "Not a valid choice, please try again\n";
    }
    cout << "Enter your choice\n0.) Exit\n1.) Create a student\n2.) Delete a student\n";
    cout <<"3.) Add books to library\n4.) Discard books in library\n5.) Issue book to a student\n";
    cout << "6.) Return a book to the library\n7.) See a student's profile\n8.) Search a book\n9.) Deduct fine amount of student\n";
    cout <<"10.) See available bids for some ISBN\n11.) Search book with publication and title\n12.) View all students\n";
    cout << "13.) View all books in the library\n14.) View return history of a student\n15.) View authors of a book\n";
    cout << "16.) View books sorted by category\n";
    cin >>i;
    }
    return 0;
}
