/****************/
/*              */
/* kiwi.db3.sql */
/*              */
/****************/

/* Disable Foreign Keys */
pragma foreign_keys = off;
/* Begin Transaction */
begin transaction;

/* Database [kiwi] */
pragma auto_vacuum=1;
pragma encoding='UTF-8';
pragma page_size=1024;

/* Drop table [main].[file_form_01] */
drop table if exists [main].[file_form_01];

/* Table structure [main].[file_form_01] */
CREATE TABLE [main].[file_form_01] (
  [file_id] INTEGER, 
  [form_recid] varchAR(50), 
  [file_name] VARCHAR(10), 
  [file_gender] NCHAR(1), 
  [file_nation] VARCHAR(10), 
  [file_birth_place] VARCHAR(50), 
  [file_birth_date] DATE, 
  [file_party] VARCHAR(10), 
  [file_inparty_date] DATE, 
  [file_inwork_date] DATE, 
  [file_proferssion] VARCHAR(50), 
  [file_full_educate_degree] VARCHAR(10), 
  [file_full_educate_place] VARCHAR(100), 
  [file_part_educate_degree] VARCHAR(10), 
  [file_part_educate_place] VARCHAR(100), 
  [file_party_rep] VARCHAR(20), 
  [file_npc_member] VARCHAR(20), 
  [file_cppcc_member] VARCHAR(20), 
  [file_work_unit] VARCHAR(50), 
  [file_current_position] VARCHAR(50), 
  [file_date_4_position] DATE, 
  [file_home_address] VARCHAR(100), 
  [file_phone] VARCHAR(20), 
  [file_resume] NVARCHAR(2000), 
  [file_photo] VARCHAR(255), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_02] */
drop table if exists [main].[file_form_02];

/* Table structure [main].[file_form_02] */
CREATE TABLE [main].[file_form_02] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_gender] VARCHAR(10), 
  [file_nation] VARCHAR(10), 
  [file_PoliticalStatus] VARCHAR(20), 
  [file_WorkingState] INTEGER, 
  [file_WorkUnit] VARCHAR(20), 
  [file_CurrentPosition] VARCHAR(20), 
  [file_Rank] VARCHAR(20), 
  [file_IDCard] VARCHAR(40), 
  [file_HouseholdAddress] VARCHAR(40), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_03] */
drop table if exists [main].[file_form_03];

/* Table structure [main].[file_form_03] */
CREATE TABLE [main].[file_form_03] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_MarriageStatus] INTEGER, 
  [file_IfChange] INTEGER, 
  [file_MaritalStatusChange] INTEGER, 
  [file_ChangeTheTime] VARCHAR(50), 
  [file_ChangingReason] VARCHAR(200), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_04] */
drop table if exists [main].[file_form_04];

/* Table structure [main].[file_form_04] */
CREATE TABLE [main].[file_form_04] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_PassportNo] VARCHAR(50), 
  [file_IssueDate] VARCHAR(20), 
  [file_ValidUntil] VARCHAR(20), 
  [file_CustodianInstitution] VARCHAR(40), 
  [file_remark] VARCHAR(40), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_05] */
drop table if exists [main].[file_form_05];

/* Table structure [main].[file_form_05] */
CREATE TABLE [main].[file_form_05] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_StartDate] VARCHAR(40), 
  [file_EndDate] VARCHAR(20), 
  [file_TheCountries] VARCHAR(50), 
  [file_reason] VARCHAR(50), 
  [file_ApprovingAuthority] VARCHAR(30), 
  [file_PassportNo] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_06] */
drop table if exists [main].[file_form_06];

/* Table structure [main].[file_form_06] */
CREATE TABLE [main].[file_form_06] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_IDName] VARCHAR(20), 
  [file_I.D.] INTEGER(50), 
  [file_StartTime] VARCHAR(40), 
  [file_EndDate] VARCHAR(20), 
  [file_CustodianInstitution] VARCHAR(30), 
  [file_remark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_07] */
drop table if exists [main].[file_form_07];

/* Table structure [main].[file_form_07] */
CREATE TABLE [main].[file_form_07] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_StartDate] VARCHAR(40), 
  [file_EndDate] VARCHAR(40), 
  [file_TheArea] VARCHAR(50), 
  [file_reason] VARCHAR(50), 
  [file_ApprovingAuthority] VARCHAR(40), 
  [file_CertificateNumber] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_08] */
drop table if exists [main].[file_form_08];

/* Table structure [main].[file_form_08] */
CREATE TABLE [main].[file_form_08] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_zinvName] VARCHAR(20), 
  [file_zinvpeiouName] VARCHAR(20), 
  [file_zinvpeiouCountry] VARCHAR(30), 
  [file_zinvpeiouWorkUnits] VARCHAR(30), 
  [file_zinvpeiouDuty] VARCHAR(30), 
  [file_zinvpeiouRegistrationTime] VARCHAR(20), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_09] */
drop table if exists [main].[file_form_09];

/* Table structure [main].[file_form_09] */
CREATE TABLE [main].[file_form_09] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_zinvName] VARCHAR(20), 
  [file_zinvpeiouName] VARCHAR(20), 
  [file_zinvpeiouArea] VARCHAR(30), 
  [file_zinvpeiouWorkUnits] VARCHAR(30), 
  [file_zinvpeiouDuty] VARCHAR(30), 
  [file_zinvpeiouRegistrationTime] VARCHAR(20), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_10] */
drop table if exists [main].[file_form_10];

/* Table structure [main].[file_form_10] */
CREATE TABLE [main].[file_form_10] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] varchAR(50), 
  [file_name] VARCHAR(20), 
  [file_moveToCountries] VARCHAR(20), 
  [file_LivingCity] VARCHAR(30), 
  [file_ImmigrationIDNumber] VARCHAR(50), 
  [file_typeOfImmigration] INTEGER, 
  [file_ImmigrationTime] VARCHAR(20), 
  [file_remark] VARCHAR(100), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_11] */
drop table if exists [main].[file_form_11];

/* Table structure [main].[file_form_11] */
CREATE TABLE [main].[file_form_11] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_CountryOrArea] VARCHAR(20), 
  [file_WorkOrLifeCity] VARCHAR(20), 
  [file_StartingTime] VARCHAR(30), 
  [file_remark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);



/* Drop table [main].[file_form_12] */
drop table if exists [main].[file_form_12];

/* Table structure [main].[file_form_12] */
CREATE TABLE [main].[file_form_12] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_spouse] INTEGER DEFAULT (-1), 
  [file_spouseName] VARCHAR(20), 
  [file_WorkOrStudyUnit] VARCHAR(20), 
  [file_TheCurrentPosition] VARCHAR(20), 
  [file_UnitOfNature1] INTEGER DEFAULT (-1), 
  [file_UnitOfNature2] INTEGER DEFAULT (-1), 
  [file_UnitOfNature3] INTEGER DEFAULT (-1), 
  [file_UnitOfNature4] INTEGER DEFAULT (-1), 
  [file_IDName] VARCHAR(20), 
  [file_IDNumber] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);



/* Drop table [main].[file_form_12_c] */
drop table if exists [main].[file_form_12_c];

/* Table structure [main].[file_form_12_c] */
CREATE TABLE [main].[file_form_12_c] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Children] VARCHAR(10), 
  [file_ChildrenName] VARCHAR(20), 
  [file_IFLiveTogetherWithChildren] INTEGER DEFAULT (-1), 
  [file_ChildrenWorkOrStudyUnit] VARCHAR(20), 
  [file_ChildrenTheCurrentPosition] VARCHAR(20), 
  [file_ChildrenUnitOfNature1] INTEGER DEFAULT (-1), 
  [file_ChildrenUnitOfNature2] inteGER DEFAULT (-1), 
  [file_ChildrenUnitOfNature3] INTEGER DEFAULT (-1), 
  [file_ChildrenUnitOfNature4] INTEGER DEFAULT (-1), 
  [file_ChildrenIDName] VARCHAR(20), 
  [file_ChildrenIDNumber] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_12_cl] */
drop table if exists [main].[file_form_12_cl];

/* Table structure [main].[file_form_12_cl] */
CREATE TABLE [main].[file_form_12_cl] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Children] VARCHAR(10), 
  [file_ChildrenName] VARCHAR(20), 
  [file_ChildrenSpouseName] VARCHAR(20), 
  [file_ChildrenSpouseWorkOrStudyUnit] VARCHAR(20), 
  [file_ChildrenSpouseTheCurrentPosition] VARCHAR(20), 
  [file_ChildrenSpouseUnitOfNature1] INTEGER DEFAULT (-1), 
  [file_ChildrenSpouseUnitOfNature2] INTEGER DEFAULT (-1), 
  [file_ChildrenSpouseUnitOfNature3] INTEGER DEFAULT (-1), 
  [file_ChildrenSpouseUnitOfNature4] INTEGER DEFAULT (-1), 
  [file_ChildrenSpouseIDName] VARCHAR(20), 
  [file_ChildrenSpouseIDNumber] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_13] */
drop table if exists [main].[file_form_13];

/* Table structure [main].[file_form_13] */
CREATE TABLE [main].[file_form_13] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_JinqinName] VARCHAR(20), 
  [file_JinqinInvestigatedTime] VARCHAR(20), 
  [file_JinqinInvestigatedReason] VARCHAR(50), 
  [file_JinqinProcessingPhase] INTEGER, 
  [file_JinqinProcessingResults] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_14] */
drop table if exists [main].[file_form_14];

/* Table structure [main].[file_form_14] */
CREATE TABLE [main].[file_form_14] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_salary] FLOAT, 
  [file_bonus] FLOAT, 
  [file_others] FLOAT, 
  [file_Total] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_15] */
drop table if exists [main].[file_form_15];

/* Table structure [main].[file_form_15] */
CREATE TABLE [main].[file_form_15] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_GiveLectures] VARCHAR(50), 
  [file_Writing] VARCHAR(50), 
  [file_consulting] VARCHAR(50), 
  [file_other] VARCHAR(50), 
  [file_total] VARCHAR(50), 
  [file_reviewing] VARCHAR(50), 
  [file_Painting] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_16] */
drop table if exists [main].[file_form_16];

/* Table structure [main].[file_form_16] */
CREATE TABLE [main].[file_form_16] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_PropertyOwnerName] VARCHAR(100), 
  [file_SourceOfRealEstate] INTEGER, 
  [file_DestOfRealEstate] INTEGER, 
  [file_TheSpecificAddress] VARCHAR(255), 
  [file_ConstructionArea] FLOAT, 
  [file_RealEstateProperties] INTEGER, 
  [file_TradingHours] VARCHAR(50), 
  [file_TheTransactionPrice] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_17] */
drop table if exists [main].[file_form_17];

/* Table structure [main].[file_form_17] */
CREATE TABLE [main].[file_form_17] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_NameOfHolder] VARCHAR(20), 
  [file_StockNameOrCode] VARCHAR(50), 
  [file_HoldingTheNumber] FLOAT, 
  [file_The market value of the previous session ] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_17_1] */
drop table if exists [main].[file_form_17_1];

/* Table structure [main].[file_form_17_1] */
CREATE TABLE [main].[file_form_17_1] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_TheTotalMarketValue] FLOAT, 
  [remark] VARCHAR(255), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_18] */
drop table if exists [main].[file_form_18];

/* Table structure [main].[file_form_18] */
CREATE TABLE [main].[file_form_18] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_NameOfHolder] VARCHAR(20), 
  [file_NameOfTheFund] VARCHAR(20), 
  [file_FundShare] FLOAT, 
  [file_AmountAtPreSession ] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_18_1] */
drop table if exists [main].[file_form_18_1];

/* Table structure [main].[file_form_18_1] */
CREATE TABLE [main].[file_form_18_1] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_TotalAmountFunds ] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_19] */
drop table if exists [main].[file_form_19];

/* Table structure [main].[file_form_19] */
CREATE TABLE [main].[file_form_19] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_NameOfApplicant] VARCHAR(20), 
  [file_Insurance products are full name] VARCHAR(100), 
  [file_Insurance policy no.] VARCHAR(50), 
  [file_Name of insurance company] VARCHAR(50), 
  [file_Accumulative pay premium, investment gold ] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_19_1] */
drop table if exists [main].[file_form_19_1];

/* Table structure [main].[file_form_19_1] */
CREATE TABLE [main].[file_form_19_1] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_TotalAmountofInsurenceFunds ] FLOAT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_20] */
drop table if exists [main].[file_form_20];

/* Table structure [main].[file_form_20] */
CREATE TABLE [main].[file_form_20] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_Unified social credit code/registration number ] INTEGER(50), 
  [file_Name of enterprise or other market subject ] VARCHAR(50), 
  [file_Set up the date ] VARCHAR(20), 
  [file_BusinessScope ] VARCHAR(50), 
  [file_registered ] VARCHAR(50), 
  [file_premises] VARCHAR(50), 
  [file_EnterpriseType] INTEGER, 
  [file_Registered capital or amount of capital ] FLOAT, 
  [file_Individual contribution or amount of capital contribution ] FLOAT, 
  [file_Individual subscribed capital contribution ratio or individual contribution ratio ] FLOAT, 
  [file_remark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_21] */
drop table if exists [main].[file_form_21];

/* Table structure [main].[file_form_21] */
CREATE TABLE [main].[file_form_21] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Depositor's name ] VARCHAR(20), 
  [file_Country and city of deposit ] VARCHAR(50), 
  [file_The full name of an opening bank or financial institution ] VARCHAR(100), 
  [file_currency ] VARCHAR(20), 
  [file_amount ] FLOAT, 
  [file_remark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_22] */
drop table if exists [main].[file_form_22];

/* Table structure [main].[file_form_22] */
CREATE TABLE [main].[file_form_22] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Name of investor ] VARCHAR(20), 
  [file_Countries and cities to invest in ] VARCHAR(50), 
  [file_Investment situation] VARCHAR(50), 
  [file_currency ] VARCHAR(20), 
  [file_Investment amount] FLOAT, 
  [file_remark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_23] */
drop table if exists [main].[file_form_23];

/* Table structure [main].[file_form_23] */
CREATE TABLE [main].[file_form_23] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Other matters that individuals deem necessary to report ] TEXT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_24_1] */
drop table if exists [main].[file_form_24_1];

/* Table structure [main].[file_form_24_1] */
CREATE TABLE [main].[file_form_24_1] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_AwardsTime] VARCHAR(20), 
  [file_AwardsName] VARCHAR(255), 
  [file_AwardsQualificationsAuthority ] VARCHAR(50), 
  [file_AwardsTheTitanic] VARCHAR(50), 
  [file_AwardsRemark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_24_2] */
drop table if exists [main].[file_form_24_2];

/* Table structure [main].[file_form_24_2] */
CREATE TABLE [main].[file_form_24_2] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_PunishTime] VARCHAR(20), 
  [file_PunishName] VARCHAR(255), 
  [file_PunishQualificationsAuthority ] VARCHAR(50), 
  [file_PunishTheTitanic] VARCHAR(50), 
  [file_PunishRemark] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_25] */
drop table if exists [main].[file_form_25];

/* Table structure [main].[file_form_25] */
CREATE TABLE [main].[file_form_25] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_ReportYear] VARCHAR(10), 
  [file_Annual cadre of cadres report on the report of integrity report ] TEXT, 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_26] */
drop table if exists [main].[file_form_26];

/* Table structure [main].[file_form_26] */
CREATE TABLE [main].[file_form_26] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_ReportYear] VARCHAR(10), 
  [file_Annual report on health] TEXT, 
  [file_ReportPic] VARCHAR(255), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_27] */
drop table if exists [main].[file_form_27];

/* Table structure [main].[file_form_27] */
CREATE TABLE [main].[file_form_27] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_ReportYear] VARCHAR(10), 
  [file_Annual report form of social morality] TEXT, 
  [file_ReportPic] VARCHAR(255), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_28] */
drop table if exists [main].[file_form_28];

/* Table structure [main].[file_form_28] */
CREATE TABLE [main].[file_form_28] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_money] FLOAT, 
  [file_Refuse or hand in gifts  name] VARCHAR(50), 
  [file_Refuse or hand in gifts number] FLOAT, 
  [file_Refuse or hand in gifts value] FLOAT, 
  [file_Refuse or hand in gifts time] DATE, 
  [file_Turned over to the department ] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_29] */
drop table if exists [main].[file_form_29];

/* Table structure [main].[file_form_29] */
CREATE TABLE [main].[file_form_29] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Run the reason ] VARCHAR(200), 
  [file_At the time ] DATE, 
  [file_held] VARCHAR(100), 
  [file_In object ] VARCHAR(100), 
  [file_participants ] FLOAT, 
  [file_Total amount of gift money ] FLOAT, 
  [file_Use number of vehicles and sources] VARCHAR(200), 
  [file_If Two reports a commitment ] VARCHAR(10), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_30] */
drop table if exists [main].[file_form_30];

/* Table structure [main].[file_form_30] */
CREATE TABLE [main].[file_form_30] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_Post risk point] VARCHAR(50), 
  [file_Risk level ] VARCHAR(50), 
  [file_The prevention and control measures ] VARCHAR(300), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_30_0] */
drop table if exists [main].[file_form_30_0];

/* Table structure [main].[file_form_30_0] */
CREATE TABLE [main].[file_form_30_0] (
  [file_id] INTEGER NOT NULL, 
  [form_recid] VARCHAR(50), 
  [file_position] VARCHAR(50), 
  [file_Job responsibilities ] VARCHAR(500), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_attachment] */
drop table if exists [main].[file_form_attachment];

/* Table structure [main].[file_form_attachment] */
CREATE TABLE [main].[file_form_attachment] (
  [file_id] INTEGER, 
  [form_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [attachment_recid] VARCHAR(50), 
  [which_attachment] INTEGER DEFAULT 1, 
  [attachment_path] VARCHAR(255), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_form_flags] */
drop table if exists [main].[file_form_flags];

/* Table structure [main].[file_form_flags] */
CREATE TABLE [main].[file_form_flags] (
  [file_id] INTEGER NOT NULL, 
  [file_4IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_4IfChange] INTEGER DEFAULT (-1), 
  [file_5IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_5IfChange] INTEGER, 
  [file_6IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_6IfChange] INTEGER DEFAULT (-1), 
  [file_7IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_7IfChange] INTEGER DEFAULT (-1), 
  [file_8IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_8IfChange] INTEGER DEFAULT (-1), 
  [file_9IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_9IfChange] INTEGER DEFAULT (-1), 
  [file_10IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_10IfChange] INTEGER DEFAULT (-1), 
  [file_11IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_11IfChange] INTEGER DEFAULT (-1), 
  [file_12IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_12IfChange] INTEGER DEFAULT (-1), 
  [file_13IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_13IfChange] INTEGER DEFAULT (-1), 
  [file_14IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_14IfChange] INTEGER DEFAULT (-1), 
  [file_15IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_15IfChange] INTEGER DEFAULT (-1), 
  [file_16IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_16IfChange] INTEGER DEFAULT (-1), 
  [file_17IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_17IfChange] INTEGER DEFAULT (-1), 
  [file_18IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_18IfChange] INTEGER DEFAULT (-1), 
  [file_19IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_19IfChange] INTEGER DEFAULT (-1), 
  [file_20IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_20IfChange] INTEGER DEFAULT (-1), 
  [file_21IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_21IfChange] INTEGER DEFAULT (-1), 
  [file_22IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_22IfChange] INTEGER DEFAULT (-1), 
  [file_23IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_23IfChange] INTEGER DEFAULT (-1), 
  [file_24IfHaveThisSituation] INTEGER DEFAULT (-1), 
  [file_24IfChange] INTEGER DEFAULT (-1));


/* Drop table [main].[file_invertigated_form_10] */
drop table if exists [main].[file_invertigated_form_10];

/* Table structure [main].[file_invertigated_form_10] */
CREATE TABLE [main].[file_invertigated_form_10] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_unit_position] VARCHAR(100), 
  [initial_check_date] VARCHAR(20), 
  [initial_check_conclusion] VARCHAR(100), 
  [initial_check_way] VARCHAR(50), 
  [register_date] VARCHAR(20), 
  [register_conclusion] VARCHAR(100), 
  [register_way] VARCHAR(50), 
  [initial_check_attachment] INTEGER DEFAULT 0, 
  [register_attachment] INTEGER DEFAULT 0, 
  [create_date] DATE DEFAULT (data()), 
  [modify_date] DATE DEFAULT (date()));


/* Drop table [main].[file_invertigated_form_11] */
drop table if exists [main].[file_invertigated_form_11];

/* Table structure [main].[file_invertigated_form_11] */
CREATE TABLE [main].[file_invertigated_form_11] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_unit_position] VARCHAR(100), 
  [being_public_date] VARCHAR(20), 
  [public_media] VARCHAR(20), 
  [main_problem_indeed] VARCHAR(200), 
  [public_problem_content] VARCHAR(1000), 
  [public_attachment] INTEGER, 
  [create_date] DATE, 
  [modify_date] DATE);



/* Drop table [main].[file_invertigated_form_12] */
drop table if exists [main].[file_invertigated_form_12];

/* Table structure [main].[file_invertigated_form_12] */
CREATE TABLE [main].[file_invertigated_form_12] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [xingfang_docno] VARCHAR(20), 
  [xingfang_date] DATE, 
  [xingfang_source_unit] VARCHAR(20), 
  [file_name] VARCHAR(20), 
  [file_position] VARCHAR(20), 
  [file_unit] VARCHAR(20), 
  [xingfang_file_name] VARCHAR(10), 
  [xingfang_file_contact] VARCHAR(20), 
  [xingfang_file_unit] VARCHAR(20), 
  [xingfang_file_position] VARCHAR(20), 
  [xingfang_content] TEXT, 
  [xingfang_inverstigation] VARCHAR(255), 
  [xingfang_conclusion] VARCHAR(100), 
  [xingfang_memo] VARCHAR(100), 
  [create_date] DATE, 
  [modify_date] DATE);



/* Drop table [main].[file_invertigated_form_13] */
drop table if exists [main].[file_invertigated_form_13];

/* Table structure [main].[file_invertigated_form_13] */
CREATE TABLE [main].[file_invertigated_form_13] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_gender] VARCHAR(4), 
  [file_idcard] VARCHAR(20), 
  [file_unit] VARCHAR(20), 
  [file_position] VARCHAR(20), 
  [acceptance_summary] VARCHAR(500), 
  [acceptance_source] VARCHAR(50), 
  [accepted_date] DATE, 
  [acceptance_source_file] VARCHAR(50), 
  [inverstigation_summary] VARCHAR(500), 
  [inverstigation_unit] CHAR, 
  [inverstigated_date] DATE, 
  [inverstigation_fact] VARCHAR(20), 
  [clearing_summary] VARCHAR(50), 
  [clearing_unit] VARCHAR(20), 
  [clearing_docno] VARCHAR(20), 
  [clearing_punish_start_date] DATE, 
  [clearing_punish_end_date] DATE, 
  [clearing_memo] VARCHAR(100), 
  [clearing_isregister] VARCHAR(4), 
  [clearing_register_date] DATE, 
  [clearing_four_xt] INTEGER, 
  [clearing_public] VARCHAR(50), 
  [clearing_public_type] VARCHAR(50), 
  [clearing_public_degree] VARCHAR(50), 
  [create_date] DATE, 
  [modify_date] DATE);


/* Drop table [main].[file_invertigated_form_14] */
drop table if exists [main].[file_invertigated_form_14];

/* Table structure [main].[file_invertigated_form_14] */
CREATE TABLE [main].[file_invertigated_form_14] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_unit_position] VARCHAR(100), 
  [touch_date] DATE, 
  [touch_file] VARCHAR(20), 
  [touch_type] VARCHAR(50), 
  [touch_reason] VARCHAR(500), 
  [touch_content] TEXT, 
  [touch_attachment] INTEGER, 
  [create_date] DATE, 
  [modify_date] DATE);



/* Drop table [main].[file_invertigated_form_15] */
drop table if exists [main].[file_invertigated_form_15];

/* Table structure [main].[file_invertigated_form_15] */
CREATE TABLE [main].[file_invertigated_form_15] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_unit_position] VARCHAR(100), 
  [pdp_type] VARCHAR(20), 
  [case_essence] VARCHAR(50), 
  [pdp_unit] CHAR, 
  [pdp_docno] CHAR, 
  [pdp_start_date] DATE, 
  [pdp_end_date] DATE, 
  [pdp_reason] TEXT, 
  [pdp_content] TEXT, 
  [pdp_attachment] INTEGER, 
  [pdp_memo] VARCHAR(100), 
  [create_date] DATE DEFAULT (date()), 
  [modify_date] DATE DEFAULT (date()));



/* Drop table [main].[file_invertigated_form_16] */
drop table if exists [main].[file_invertigated_form_16];

/* Table structure [main].[file_invertigated_form_16] */
CREATE TABLE [main].[file_invertigated_form_16] (
  [file_id] INTEGER, 
  [form_recid] VARCHAR(50), 
  [file_name] VARCHAR(20), 
  [file_unit_position] VARCHAR(100), 
  [odp_type] VARCHAR(20), 
  [case_essence] VARCHAR(50), 
  [odp_unit] CHAR, 
  [odp_docno] CHAR, 
  [odp_start_date] DATE, 
  [odp_end_date] DATE, 
  [odp_reason] TEXT, 
  [odp_content] TEXT, 
  [odp_attachment] INTEGER, 
  [odp_memo] VARCHAR(100), 
  [create_date] DATE DEFAULT (date()), 
  [modify_date] DATE DEFAULT (date()));


/* Drop table [main].[form_type] */
drop table if exists [main].[form_type];

/* Table structure [main].[form_type] */
CREATE TABLE [main].[form_type] (
  [type_id] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 
  [type_serial] VARCHAR(10), 
  [type_name] VARCHAR(100), 
  [type_description] VARCHAR(50));

/* Data [main].[form_type] */
insert into [main].[form_type] values(1, '表1', '科级干部基本情况登记表', '个人填写');
insert into [main].[form_type] values(2, '表2-1', '报告人基本情况', '个人填写');
insert into [main].[form_type] values(3, '表2-2', '《规定》第三条所列事项1', '个人填写');
insert into [main].[form_type] values(4, '表2-3', '《规定》第三条所列事项2', '个人填写');
insert into [main].[form_type] values(5, '表2-4', '《规定》第三条所列事项3', '个人填写');
insert into [main].[form_type] values(6, '表2-5', '《规定》第三条所列事项4', '个人填写');
insert into [main].[form_type] values(7, '表2-6', '《规定》第三条所列事项5', '个人填写');
insert into [main].[form_type] values(8, '表2-7', '《规定》第四条所列事项1', '个人填写');
insert into [main].[form_type] values(9, '表2-8', '《规定》第四条所列事项2', '个人填写');
insert into [main].[form_type] values(10, '表2-9', '《规定》第四条所列事项3', '个人填写');
insert into [main].[form_type] values(11, '表2-10', '《规定》第四条所列事项4', '个人填写');
insert into [main].[form_type] values(12, '表2-11', '《规定》第四条所列事项5', '个人填写');
insert into [main].[form_type] values(13, '表2-12', '《规定》第四条所列事项6', '个人填写');
insert into [main].[form_type] values(14, '表2-13', '《规定》第四条所列事项7', '个人填写');
insert into [main].[form_type] values(15, '表2-14', '《规定》第四条所列事项8', '个人填写');
insert into [main].[form_type] values(16, '表2-15', '《规定》第四条所列事项9', '个人填写');
insert into [main].[form_type] values(17, '表2-16', '个人有认为需要报告的其他事项', '个人填写');
insert into [main].[form_type] values(18, '表3', '科级干部奖惩情况登记表', '个人填写');
insert into [main].[form_type] values(19, '表4', '年度科级干部述责述廉报告表', '个人填写');
insert into [main].[form_type] values(20, '表5', '年度科级干部健康情况报告表', '个人填写');
insert into [main].[form_type] values(21, '表6', '年度科级干部社会公德情况报告表', '个人填写');
insert into [main].[form_type] values(22, '表7', '科级干部拒收或上交礼金、礼品情况登记表', '个人填写');
insert into [main].[form_type] values(23, '表8', '科级干部参与操办本人及近亲属婚丧喜庆事宜情况报告表', '个人填写');
insert into [main].[form_type] values(24, '表9', '科级干部岗位风险防控情况报告表', '个人填写');
insert into [main].[form_type] values(25, '表10', '科级干部接受组织调查情况表', '纪委填写');
insert into [main].[form_type] values(26, '表11', '科级干部违纪问题被通报情况表', '纪委填写');
insert into [main].[form_type] values(27, '表12', '科级干部信访举报调查处理情况表', '纪委填写');
insert into [main].[form_type] values(28, '表13', '科级干部问题线索处理情况表', '纪委填写');
insert into [main].[form_type] values(29, '表14', '科级干部廉政谈话情况表', '纪委填写');
insert into [main].[form_type] values(30, '表15', '科级干部党纪处分情况表', '纪委填写');
insert into [main].[form_type] values(31, '表16', '科级干部政纪处分情况表', '纪委填写');


/* Drop table [main].[four_punish_category] */
drop table if exists [main].[four_punish_category];

/* Table structure [main].[four_punish_category] */
CREATE TABLE [main].[four_punish_category] (
  [punish_id] integer PRIMARY KEY AUTOINCREMENT, 
  [first_category] INTEGER, 
  [category_name] VARCHAR(20), 
  [punish_type] INTEGER);

/* Data [main].[four_punish_category] */
insert into [main].[four_punish_category] values(1, -1, '谈话类', null);
insert into [main].[four_punish_category] values(2, -1, '组织处理类', null);
insert into [main].[four_punish_category] values(3, -1, '问责类', null);
insert into [main].[four_punish_category] values(4, -1, '党纪处理类', null);
insert into [main].[four_punish_category] values(5, -1, '政纪处理类', null);
insert into [main].[four_punish_category] values(6, -1, '违法处理类', null);
insert into [main].[four_punish_category] values(8, 1, '提醒谈话', 1);
insert into [main].[four_punish_category] values(9, 1, '约谈', 1);
insert into [main].[four_punish_category] values(10, 1, '诫勉谈话', 3);
insert into [main].[four_punish_category] values(11, 1, '函询', 1);
insert into [main].[four_punish_category] values(12, 2, '批评教育', 1);
insert into [main].[four_punish_category] values(13, 2, '通报批评', 1);
insert into [main].[four_punish_category] values(14, 2, '调离岗位', 2);
insert into [main].[four_punish_category] values(15, 2, '降职', 2);
insert into [main].[four_punish_category] values(16, 2, '责令辞职', 2);
insert into [main].[four_punish_category] values(17, 2, '免职', 2);
insert into [main].[four_punish_category] values(18, 3, '公开道歉', 2);
insert into [main].[four_punish_category] values(19, 3, '停职检查', 2);
insert into [main].[four_punish_category] values(20, 3, '引咎辞职', 2);
insert into [main].[four_punish_category] values(21, 3, '责令辞职', 2);
insert into [main].[four_punish_category] values(22, 3, '免职', 2);
insert into [main].[four_punish_category] values(23, 4, '警告', 2);
insert into [main].[four_punish_category] values(24, 4, '严重警告', 2);
insert into [main].[four_punish_category] values(25, 4, '撤销党内职务', 3);
insert into [main].[four_punish_category] values(26, 4, '留党察看', 3);
insert into [main].[four_punish_category] values(27, 4, '开除党籍', 4);
insert into [main].[four_punish_category] values(28, 5, '警告', 2);
insert into [main].[four_punish_category] values(29, 5, '严重警告', 2);
insert into [main].[four_punish_category] values(30, 5, '记过', 2);
insert into [main].[four_punish_category] values(31, 5, '记大过', 2);
insert into [main].[four_punish_category] values(32, 5, '降级', 3);
insert into [main].[four_punish_category] values(33, 5, '撤职', 3);
insert into [main].[four_punish_category] values(34, 5, '开除', 4);
insert into [main].[four_punish_category] values(35, 6, '被司法机关起诉但', 4);
insert into [main].[four_punish_category] values(36, 6, '被司法机关给予管制', 4);


/* Drop table [main].[kiwi_users] */
drop table if exists [main].[kiwi_users];

/* Table structure [main].[kiwi_users] */
CREATE TABLE [main].[kiwi_users] (
  [user_name] VARCHAR(20), 
  [user_pwd] VARCHAR(50), 
  [user_group] INTEGER DEFAULT 3, 
  [last_login_date] VARCHAR(50));

/* Data [main].[kiwi_users] */
insert into [main].[kiwi_users] values('admin', '4acb4bc224acbbe3c2bfdcaa39a4324e', 0, null);

/* Drop table [main].[orgnization_file] */
drop table if exists [main].[orgnization_file];

/* Table structure [main].[orgnization_file] */
CREATE TABLE [main].[orgnization_file] (
  [file_id] integer PRIMARY KEY AUTOINCREMENT, 
  [file_name] varchar(50), 
  [file_phone] VARCHAR(20), 
  [folder_name] VARCHAR(50), 
  [del_status] INTEGER DEFAULT 0);


/* Drop table [main].[orgnization_folder] */
drop table if exists [main].[orgnization_folder];

/* Table structure [main].[orgnization_folder] */
CREATE TABLE [main].[orgnization_folder] (
  [folder_id] integer PRIMARY KEY AUTOINCREMENT, 
  [folder_name] varchar(50), 
  [folder_contact] VARCHAR(20), 
  [contact_tel] VARCHAR(20), 
  [contact_phone] VARCHAR(20), 
  [del_status] INTEGER DEFAULT 0);


/* Drop table [main].[personal_form_info] */
drop table if exists [main].[personal_form_info];

/* Table structure [main].[personal_form_info] */
CREATE TABLE [main].[personal_form_info] (
  [file_id] INTEGER, 
  [form_id] INTEGER, 
  [form_serial] VARCHAR(20), 
  [create_date] VARCHAR(20), 
  [modify_date] VARCHAR(20));


/* Commit Transaction */
commit transaction;

/* Enable Foreign Keys */
pragma foreign_keys = on;
