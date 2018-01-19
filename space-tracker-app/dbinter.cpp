#include "dbinter.h"

static int callBack(void *data, int argc, char **argv, char **azColName)
{
   QList<Information> *lst = (QList<Information> *)data;
   Information someInfo;
   someInfo.Type = TLEInfo;
   TLE someTLE;
   someTLE.nor_id = atoi(argv[0]);
   memcpy(someTLE.name, argv[2], 25);
   someTLE.cl = argv[3][0];
   memcpy(someTLE.i_n_s, argv[4], 2);
   someTLE.i_n_n = atoi(argv[5]);
   memcpy(someTLE.i_n_p, argv[6], 3);
   memcpy(someTLE.era, argv[7], 2);
   someTLE.era_t = std::strtod(argv[8], 0);
   someTLE.der = std::strtod(argv[9], 0);
   someTLE.der2 = std::strtod(argv[10], 0);
   someTLE.b = std::strtod(argv[11], 0);
   someTLE.efi = argv[12][0];
   someTLE.num = atoi(argv[13]);
   someTLE.sum =argv[14][0]-(int)'0';
   someTLE.incl = std::strtod(argv[15], 0);
   someTLE.lg = std::strtod(argv[16], 0);
   someTLE.ex = std::strtod(argv[17], 0);
   someTLE.arg_per = std::strtod(argv[18], 0);
   someTLE.aver_anom = std::strtod(argv[19], 0);
   someTLE.freq = std::strtod(argv[20], 0);
   someTLE.era_num = atoi(argv[21]);
   someTLE.sum_2 = argv[22][0]-(int)'0';
   someInfo.TLEI = someTLE;
   someInfo.TLEstr1 = (argv[23]);//UPD
   someInfo.TLEstr2 = (argv[24]);//UPD
   lst->append(someInfo);
   return 0;
}


DBInter::DBInter()
{
    try
    {
        int rc;
        rc =  sqlite3_open(DirectoryDataBase, &db);
        if (rc)
            throw DataBaseOpen();
    }
    catch (BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error: DBIner", error.what());
    }
    return;
}

DBInter::~DBInter()
{
    sqlite3_close(db);
}

QList<Information> DBInter::loadAllTLE(const Date &dt)
{
    char *zErrMsg = 0;
    int rc;
    QList<Information> resInfo;
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    std::string fsd = d1.toString(QString("yyyy-MM-dd")).toStdString();
    std::string str = "SELECT * FROM TLE WHERE (DATE = ";
    str += '\'';
    str += fsd;
    str += '\'';
    str += ");";
    rc = sqlite3_exec(db, str.c_str(), callBack, (void*)&resInfo, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        throw SQLiteError();
    }
    return resInfo;
}

QList<Information> DBInter::loadAllSSR(const Date &)
{
    QList<Information> resInfo;
    return resInfo;
}

QList<Information> DBInter::loadSSR(const unsigned long &id, const Date &)
{
     QList<Information> resInfo;
     return resInfo;
}

QList<Information> DBInter::loadTLE(const unsigned long &id, const Date &dt)
{
    char *zErrMsg = 0;
    int rc;
    QList<Information> resInfo;
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    std::string fsd = d1.toString(QString("yyyy-MM-dd")).toStdString();
    std::string str = "SELECT * FROM TLE WHERE ((DATE = ";
    str += '\'';
    str += fsd;
    str += '\'';
    str += ") AND (NOR_ID  = ";
    str += std::to_string(id);
    str += "));";
    rc = sqlite3_exec(db, str.c_str(), callBack, (void*)&resInfo, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        throw SQLiteError();
    }
    return resInfo;
}

void DBInter::addTLE(QList<Information> data, const Date &date)
{
    QList<Information>::iterator i;
    for (i = data.begin(); i != data.end(); ++i)
    {
        if ((*i).Type == TLEInfo)
            addTLE((*i).TLEI, date);
    }
    return;
}

void DBInter::addSSR(QList<Information>, const Date &)
{
    return;
}

void DBInter::addTLE(TLE tl,const Date &dt)
{
    char *zErrMsg = 0;
    int rc;
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    std::stringstream st;
    std::string str = "INSERT INTO TLE (NOR_ID ,"\
                                        "DATE,"\
                                        "NAME,"\
                                        "CL,"\
                                        "I_N_S,"\
                                        "I_N_N,"\
                                        "I_N_P,"\
                                        "ERA,"\
                                        "ERA_T,"\
                                        "DER,"\
                                        "DER2,"\
                                        "B,"\
                                        "EFI,"\
                                        "NUM,"\
                                        "SUM,"\
                                        "INCL,"\
                                        "LG,"\
                                        "EX,"\
                                        "ARG_PER,"\
                                        "AVER_ANOM,"\
                                        "FREQ,"\
                                        "ERA_NUM,"\
                                        "SUM_2)  VALUES (";
    str += std::to_string(tl.nor_id);
    str += ", ";
    str += '\'';
    str += d1.toString(QString("yyyy-MM-dd")).toStdString();
    str += '\'';
    str += ", ";
    str += '\'';
    str += std::string(tl.name);
    str += '\'';
    str += ", ";
    str += '\'';
    str += tl.cl;
    str += '\'';
    str += ", ";
    str += '\'';
    str += tl.i_n_s[0];
    str += tl.i_n_s[1];
    str += '\'';
    str += ", ";
    str += std::to_string(tl.i_n_n);
    str += ", ";
    str += '\'';
    for(unsigned int i = 0; i < sizeof(tl.i_n_p) / sizeof(char); i++)
    {
        str += tl.i_n_p[i];
    }
    str += '\'';
    str += ", ";
    str += '\'';
    for(unsigned int i = 0; i < sizeof(tl.era) / sizeof(char); i++)
    {
        str += tl.era[i];
    }
    str += '\'';
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.era_t;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.der;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.der2;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.b;
    str += st.str();
    st.str("");
    str += ", ";
    str += '\'';
    str += tl.efi+int('0');
    str += '\'';
    str += ", ";
    str += std::to_string(tl.num);
    str += ", ";
    str += '\'';
    str += std::to_string(tl.sum);
    str += '\'';
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.incl;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.lg;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.ex;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.arg_per;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.aver_anom;
    str += st.str();
    st.str("");
    str += ", ";
    st << std::fixed << std::setprecision(20) << tl.freq;
    str += st.str();
    st.str("");
    str += ", ";
    str += std::to_string(tl.era_num);
    str += ", ";
    str += '\'';
    str += tl.sum_2;
    str += '\'';
    str += ");";
    rc = sqlite3_exec(db, str.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
        throw SQLiteError();
    }
    std::cout << str << '\n';
    std::cout << '\n';
}

void DBInter::addSSR(SSR,const Date &)
{
    return;
}
