#include "dbinter.h"
#include "config.h"

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

DBInsertQuery::DBInsertQuery() {
    query = "INSERT INTO TLE (NOR_ID ,"\
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
}

void DBInsertQuery::addLineBreak() {
    query += '\'';
    query += ", ";
    query += '\'';
}
void DBInsertQuery::addCloseBrackets() {
    query += ');';
}
std::string DBInsertQuery::getQuery() {
    return query;
}

template<typename T>
void DBInsertQuery::addParameter(T param) {
    query += param;
    addLineBreak();
}

template<typename T>
void DBInsertQuery::addPrecisedParameter(T param) {
    std::stringstream st;
    st << std::fixed << std::setprecision(20) << param;
    query += st.str() + ", ";
}
template<typename T>
void DBInsertQuery::addParameterArray(T param) {
    std::string str;
    for(unsigned int i = 0; i < sizeof(param) / sizeof(char); i++)
    {
        str += param[i];
    }
    this->addParameter(str);
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
    std::string str = SELECT_BY_DATE;
    str += '\'';
    str += fsd;
    str += '\'';
    str += ");";
    rc = sqlite3_exec(db, str.c_str(), callBack, (void*)&resInfo, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
        throw SQLiteError();
    }
    return resInfo;
}

QList<Information> DBInter::loadTLE(const unsigned long &id, const Date &dt)
{
    char *zErrMsg = 0;
    int rc;
    QList<Information> resInfo;
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    std::string fsd = d1.toString(QString("yyyy-MM-dd")).toStdString();
    std::string str = SELECT_BY_DATE;
    str += '\'';
    str += fsd;
    str += '\'';
    str += ") AND (NOR_ID  = ";
    str += std::to_string(id);
    str += "));";
    rc = sqlite3_exec(db, str.c_str(), callBack, (void*)&resInfo, &zErrMsg);
    if (rc != SQLITE_OK)
    {
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

void DBInter::addTLE(TLE tl,const Date &dt)
{
    char *zErrMsg = 0;
    int rc;
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    DBInsertQuery qry;

    qry.addParameter(std::to_string(tl.nor_id));
    qry.addParameter(d1.toString(QString("yyyy-MM-dd")).toStdString());
    qry.addParameter(std::string(tl.name));
    qry.addParameter(tl.cl);
    qry.addParameter(tl.i_n_s[0] + tl.i_n_s[1]);
    qry.addParameter(std::to_string(tl.i_n_n));
    qry.addParameterArray(tl.i_n_p);
    qry.addParameterArray(tl.era);
    qry.addPrecisedParameter(tl.era_t);
    qry.addPrecisedParameter(tl.der);
    qry.addPrecisedParameter(tl.der2);
    qry.addPrecisedParameter(tl.b);
    qry.addParameter(tl.efi+int('0'));
    qry.addParameter(std::to_string(tl.num));
    qry.addParameter(std::to_string(tl.sum));
    qry.addPrecisedParameter(tl.incl);
    qry.addPrecisedParameter(tl.lg);
    qry.addPrecisedParameter(tl.ex);
    qry.addPrecisedParameter(tl.arg_per);
    qry.addPrecisedParameter(tl.aver_anom);
    qry.addPrecisedParameter(tl.freq);
    qry.addParameter(std::to_string(tl.era_num));
    qry.addParameter(tl.sum_2);
    qry.addCloseBrackets();

    rc = sqlite3_exec(db, qry.getQuery().c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
        throw SQLiteError();
    }
}

