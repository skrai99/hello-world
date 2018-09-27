#include "BW_DocInjector.hpp"
#include "BW_Logger.hpp"

using std::cout;


BW_DocInjector::BW_DocInjector()
{
	tDTDocumentType			=	NULLTAG;
	tDTDocumentRevType		=	NULLTAG;
}

/******************************************************************************************************************************************
Function   :TypeToRefMap(string key)
Description : The function map file extension to type of TC named reference

******************************************************************************************************************************************/
string BW_DocInjector::TypeToRefMap(string key)
{
	transform(key.begin(), key.end(), key.begin(),(int (*)(int))tolower);
	unordered_map<string, string> mapTypeToRef;
	mapTypeToRef["txt"]		= "Text";
	mapTypeToRef["csv"]		= "Text";
	mapTypeToRef["pdf"]		= "PDF_Reference";
	mapTypeToRef["docx"]	= "word";
	mapTypeToRef["doc"]		= "word";
	mapTypeToRef["docm"]	= "Fnd0word";
	mapTypeToRef["xls"]		= "excel";
	mapTypeToRef["xlsx"]	= "excel";
	mapTypeToRef["xlsm"]	= "excel";
	mapTypeToRef["drw"]		= "DrwFile";
	mapTypeToRef["prt"]		= "PrtFile";
	mapTypeToRef["asm"]		= "AsmFile";
	mapTypeToRef["jpeg"]	= "JPEG_Reference";
	mapTypeToRef["jpg"]		= "JPEG_Reference";
	mapTypeToRef["ppt"]		= "powerpoint";
	mapTypeToRef["pptx"]	= "powerpoint";
	mapTypeToRef["tif"]		= "TIF_Reference";
	mapTypeToRef["tiff"]	= "TIF_Reference";
	mapTypeToRef["zip"]		= "ZIPFILE";
	mapTypeToRef["msg"]		= "Outlook-Msg";
	mapTypeToRef["stl"]		= "STL-bin";
	mapTypeToRef["dxf"]		= "DXF";
	mapTypeToRef["log"]		= "Text";
	mapTypeToRef["rtf"]		= "BWR3_rtf";
	mapTypeToRef["png"]		= "Image";
	mapTypeToRef["htm"]		= "HTML";
	mapTypeToRef["html"]	= "HTML";
	mapTypeToRef["cgm"]		= "catcgm";
	mapTypeToRef["bmp"]		= "Image";
	mapTypeToRef["gif"]		= "Image";
	mapTypeToRef["eps"]		= "Image";
	mapTypeToRef["pwd"]		= "MISC_TEXT";
	mapTypeToRef["stp"]		= "MISC_TEXT";
	mapTypeToRef["mdi"]		= "MISC_TEXT";
	
	if(mapTypeToRef.count(key))
	{
		return mapTypeToRef.at(key);
	}
	else
	{
		//logger.writebothlog("The FileType " + key + " is not valid");
		return "MISC_TEXT";
	}
}

/******************************************************************************************************************************************
Function   :TypeToDtsMap(string key)
Description : The function map file extension to type of TC Dataset

******************************************************************************************************************************************/
string BW_DocInjector::TypeToDtsMap(string key)
{
	transform(key.begin(), key.end(), key.begin(),(int (*)(int))tolower);
	unordered_map<string, string> mapTypeToDts;
	mapTypeToDts["jpeg"]	= "jpeg";
	mapTypeToDts["jpg"]		= "jpeg";
	mapTypeToDts["txt"]		= "Text";
	mapTypeToDts["csv"]		= "Text";
	mapTypeToDts["pdf"]		= "PDF";
	mapTypeToDts["docx"]	= "MSWordX";
	mapTypeToDts["doc"]		= "MSWord";
	mapTypeToDts["docm"]	= "MSWordX";
	mapTypeToDts["xls"]		= "MSExcel";
	mapTypeToDts["xlsx"]	= "MSExcelX";
	mapTypeToDts["xlsm"]	= "MSExcelX";
	mapTypeToDts["drw"]		= "ProDrw";
	mapTypeToDts["prt"]		= "ProPrt";
	mapTypeToDts["asm"]		= "ProAsm";
	mapTypeToDts["pptx"]	= "MSPowerPointX";
	mapTypeToDts["ppt"]		= "MSPowerPoint";
	mapTypeToDts["tif"]		= "TIF";
	mapTypeToDts["tiff"]	= "TIF";
	mapTypeToDts["zip"]		= "Zip";
	mapTypeToDts["msg"]		= "Outlook";
	mapTypeToDts["stl"]		= "STL";
	mapTypeToDts["dxf"]		= "DXF";
	mapTypeToDts["log"]		= "Text";
	mapTypeToDts["rtf"]		= "MSWordX";
	mapTypeToDts["png"]		= "Image";
	mapTypeToDts["htm"]		= "HTML";
	mapTypeToDts["html"]	= "HTML";
	mapTypeToDts["cgm"]		= "CATcgm";
	mapTypeToDts["bmp"]		= "Bitmap";
	mapTypeToDts["gif"]		= "Image";
	mapTypeToDts["eps"]		= "Postscript";
	mapTypeToDts["pwd"]		= "MISC";
	mapTypeToDts["stp"]		= "MISC";
	mapTypeToDts["mdi"]		= "MISC";
	
	if(mapTypeToDts.count(key))
	{
		return mapTypeToDts.at(key);
	}
	else
	{
		//logger.writebothlog("The FileType " + key + " is not valid");
		return "MISC";
	}
}

/******************************************************************************************************************************************
Function   :DocTypeMap(string key)
Description : The function map windchill doc type to Teamcenter DT_Document name LOV

******************************************************************************************************************************************/
string BW_DocInjector::DocTypeMap(string key)
{
	unordered_map<string, string> mDocType;

    mDocType["C-Curve"]					 = "Performance Curve";
    mDocType["Customer Drawing"]		 = "Customer Drawing";
    mDocType["Engineering Standard"]	 = "Engineering Standard";
    mDocType["Spec"]					 = "Specification";
    mDocType["P-Spec"]					 = "Performance Specification";
	mDocType["Reference Document"]		 = "Reference Document";
    mDocType["Remy Document"]			 = "Remy Document";
    mDocType["Service Master Drawing"]   = "Service Master Drawing";
    mDocType["T-Spec"]					 = "Test Specification";
    mDocType["Change Object"]			 = "Change Object";
    mDocType["M-Spec"]					 = "Material Specification";
    mDocType["Customer Interface Spec"]  = "Customer Specification";
	mDocType["P&D Spec"]				 = "Specification";
	
	if(mDocType.count(key))
	{
		return mDocType.at(key);
	}
	else
	{
		return "Remy Document";
	}
}

/******************************************************************************************************************************************
Function   :findItemByItemID(const char* cItemID, tag_t& tItem)
Description : The function returns Tag of item using item id

******************************************************************************************************************************************/
int BW_DocInjector::findItemByItemID(const char* cItemID, tag_t& tItem)
	{
		int				status					=	ITK_ok;
	int 			iNumAttributes			=	1;
	int 			iNumItems				=	0;
	int				iItemNumber				=	0;

	const char		*cAttributeNames[1]		=	{"item_id"},
					*cAttributeValues[1]	=	{cItemID};

	char			*cObjectType			=	NULL;

	tag_t			*tItemTags				=	NULL;

	ITK( ITEM_find_items_by_key_attributes	(	iNumAttributes,
												cAttributeNames,
												cAttributeValues,
												&iNumItems,&tItemTags	) );
	
	if(status == ITK_ok && tItemTags != NULL && iNumItems != 0)
    {
		while( iItemNumber != iNumItems )
		{
			ITK( AOM_ask_value_string(tItemTags[iItemNumber], "object_type", &cObjectType) );
			if(tc_strcmp(cObjectType, "DT_Document")==0)
			{
				tItem = tItemTags[iItemNumber];
				MEM_free(tItemTags);
				tItemTags = NULL;
				SAFE_MEM_FREE(cObjectType);
				return 1;
			}
			iItemNumber++;
			SAFE_MEM_FREE(cObjectType);
		}
		MEM_free(tItemTags);
		tItemTags = NULL;
		return 4;
    }
	return 2;
	}


/******************************************************************************************************************************************
	Function   :findItemRev(const char* cItemID, const char* cRevId, tag_t& tItemRev)
	Description : The function returns Tag of item revision

	******************************************************************************************************************************************/
int BW_DocInjector::findItemRev(const char* cItemID, const char* cRevId, tag_t& tItemRev)
	{
		int				status					=	ITK_ok;
	int 			iNumAttributes			=	1;
	int 			iNumItems				=	0;
	int				iItemNumber				=	0;
	const char * 	cAttributeNames[1];
	const char * 	cAttributeValues[1];
	tag_t *			tItems				= NULL;
	char			*cObjectType			=	NULL;

	cAttributeNames[0] = "item_id";
	cAttributeValues[0] = cItemID;

	ITK( ITEM_find_item_revs_by_key_attributes	(	iNumAttributes,
												cAttributeNames,
												cAttributeValues,
												cRevId,
												&iNumItems,
												&tItems) );

	if(status == ITK_ok && tItems != NULL && iNumItems !=0)
	{
		while( iItemNumber != iNumItems )
		{
			ITK( AOM_ask_value_string(tItems[iItemNumber], "object_type", &cObjectType) );
			if(tc_strcmp(cObjectType, "DT_Document Revision")==0)
			{
				tItemRev = tItems[iItemNumber];
				SAFE_MEM_FREE(cObjectType);
				MEM_free(tItems);
				tItems = NULL;
				return 1;
			}
			iItemNumber++;
			SAFE_MEM_FREE(cObjectType);
		}
		MEM_free(tItems);
		tItems = NULL;
		return 4;
	}

	return 2;
	} 

/******************************************************************************************************************************************
Function    : insertPart(string inputDir)
Description : The function creates query and calls DBLogin.cpp constructor to connect to Correct DB using DB_Properties.cpp and 
			  get results of query from DB into string vector

******************************************************************************************************************************************/
void BW_DocInjector::insertPart(string inputDir,string sClassification)
{
	int status = ITK_ok;
	int iCount =0;

	//logger = BW_Logger(inputDir,sItemID);

	POM_set_env_info(POM_bypass_attr_update, FALSE, 0, 0, NULLTAG, NULL);

	string query = "SELECT [DOCUMENTNUMBER],[DOCUMENTREVISION],[NAME],[OBJECT_DESC],[CREATED_BY],[CREATION_DATE],[LAST_MODIFIED_BY],";
	query += "[LAST_MODIFIED_DATE] ,[LIFECYCLE_STATE],[RELEASE_DATE],[DOCUMENT_TYPE],[CUSTOMER_SUPL_REV],[FILE_PATH],";
	query += "[FILE_ORIGINAL_NAME],[FILE_TYPE],[MIGRATION_TYPE],[MIGRATION_DECISION],[TC_PROCESS_STATUS],[REFERENCE_REVISION],DELTA FROM [WC2TC_DOCUMENT_PHASED] WHERE  [TC_PROCESS_STATUS]!=1 AND CLASSIFICATION like '";
	query += sClassification;	query += "%'";	


	TCTYPE_find_type("DT_Document", NULL, &tDTDocumentType );
	TCTYPE_find_type("DT_Document Revision", NULL, &tDTDocumentRevType );

	dbObj = BW_DBLogin(inputDir);
	status = dbObj.loginToDB();
	if(status != ITK_ok)
	{
		logger.writebothlog("ERROR: Unable to Login to Database ");
		return;
	}

	vector<string> AllRows = dbObj.executeQuery(query,20);

	cout << "size of the file : " << AllRows.size();

	if(AllRows.size()==0)						//Item not found in staging DB
	{
		logger.writebothlog("\tError: The Requested Data with status INPROGRESS is not present in Staging Database");
	}

	tag_t tDTDocRevision=NULLTAG;


	//get how many we need to run from command prompt
	/*string sBound = ITK_ask_cli_argument("-bound");
	int iBound = atoi(sBound.c_str());
	for(int inx = 0; inx <iBound; inx++)*/

	for(int inx = 0; inx < AllRows.size(); inx++)
	{
		string row = AllRows.at(inx);

		char *	cItemID				=	tc_strtok ((char*)row.c_str(), "!");
		char *	cRevID				=	tc_strtok (NULL, "!");

		 tDTDocRevision = createItemRevision((char*)AllRows.at(inx).c_str());

		//logger.writebothlog("===================================================================================================================================================================================");
	
	}

		POM_set_env_info(POM_bypass_attr_update, TRUE, 0, 0, NULLTAG, NULL);

	//send mail code
	//sendEmailToPerson(inputDir,tDTDocRevision);

	//sendEmailOfFailedObjectToPerson(inputDir );
}

/******************************************************************************************************************************************
Function    : createItemRevision(char* irData)
Description : Receives the data of single part and creates it in teamcenter as DT_Document , calls multiple functions for attribute updation, 
			  Dataset creation etc and also write back results to staging DB. 

******************************************************************************************************************************************/
tag_t BW_DocInjector::createItemRevision(char* irData)
{
	
	int		status				=	ITK_ok;
	int		iTCProcessStatus	=	1;

	char *	cItemID				=	tc_strtok (irData, "!");
	char *	cRevID				=	tc_strtok (NULL, "!");
	char *	cItemN				=	tc_strtok (NULL, "!");
	char *	cItemDesc			=	tc_strtok (NULL, "!");
	char *	cCreatedBy			=	tc_strtok (NULL, "!");
	char *	cCreationDate		=	tc_strtok (NULL, "!");
	char *	cLastModBy			=	tc_strtok (NULL, "!");
	char *	cModDate			=	tc_strtok (NULL, "!");
	char *	cStatus				=	tc_strtok (NULL, "!");
	char *	cRelDate			=	tc_strtok (NULL, "!");
	char *  cDocType			=	tc_strtok (NULL, "!");
	char *	cCustSuplNo			=	tc_strtok (NULL, "!");
	char *  cFilePath			=	tc_strtok (NULL, "!");
	char *  cFileOrigName		=	tc_strtok (NULL, "!");
	char *  cFileType			=	tc_strtok (NULL, "!");
	char *	cMigrationType		=	tc_strtok (NULL, "!");
	char *	cMigrationDes		=	tc_strtok (NULL, "!");
	char *	cTCProcessStatus	=	tc_strtok (NULL, "!");
	char *	cReferenceRevision  =	tc_strtok (NULL, "!"); 
	char *	cDelta				=	tc_strtok (NULL, "!"); 

	date_t	dtCreationDate;
	date_t	dtLastModDate;
	date_t	dtRelDate;

	string sCreationDate(cCreationDate);
	string sModDate(cModDate);

	tag_t	tItem				=	NULLTAG;
	tag_t	tItemRev			=	NULLTAG;
	tag_t	tOwner				=	NULLTAG;
	tag_t	tModifiedBy			=	NULLTAG;
	tag_t	tCreateItem			=	NULLTAG;
	tag_t	tCreateItemRev		=	NULLTAG;
	tag_t	tRelStatus			=	NULLTAG;
	tag_t	attr_id_dateRel		=	NULLTAG;

	tag_t	tDataset			=	NULLTAG;


	string sItemName = DocTypeMap(cDocType);

	string sReleaseStatus = getreleasestatus(cStatus);

	//cout<<sItemName;

	const char *cItemName = sItemName.c_str();

	string	sTCItemID			= cItemID;
	//check if documentnumber present in WC2TC_DUPLICATE_DOC table
	string getItemID = "SELECT ITEM_ID FROM WC2TC_DUPLICATE_DOC WHERE DOCUMENTNUMBER = '";	getItemID+=cItemID;	getItemID+="'";
	vector<string> vID = dbObj.executeQuery(getItemID,1);
	if(vID.size()>0)
	{
		//duplicate ID present
		char * cItID				=	tc_strtok ((char*)vID.at(0).c_str(), "!");
		sTCItemID = cItID;
		logger.writebothlog("\nDuplicate ID found : " + string(cItemID) + " : " + sTCItemID);
	}
	vID.clear();

	cout<<"\n processing item id and Rev id is \t " <<cItemID <<cRevID;

	if(tc_strcmp(cMigrationType,"1") == 0 && tc_strcmp(cMigrationDes,"0") == 0 && tc_strcmp(cTCProcessStatus,"1") != 0)
	{
		findItemByItemID(sTCItemID.c_str(), tItem);
		if(tItem == NULL)
		{
			int myPOMMark = 0;
            if (status = POM_place_markpoint( &myPOMMark ) != ITK_ok)
			{
				logger.write(IntToString(status) + "POM-place-markpoint");
            }

			ITK( TCTYPE_construct_create_input	( tDTDocumentType, &tCreateItem ) );
			ITK( TCTYPE_construct_create_input	( tDTDocumentRevType, &tCreateItemRev ) );

			ITK(AOM_set_value_string(tCreateItem, "item_id", sTCItemID.c_str() ) );
			ITK(AOM_set_value_string(tCreateItem, "object_name", cItemName));

			
			if( tc_strcmp(cItemDesc, "") != 0)
			{
				string sItemDesc(cItemDesc);
				transform(sItemDesc.begin(), sItemDesc.end(), sItemDesc.begin(),(int (*)(int))tolower);

				if(tc_strcmp(sItemDesc.c_str(),"null") == 0)
				{
					ITK(AOM_set_value_string(tCreateItem, "object_desc", cItemN));
					ITK(AOM_set_value_string(tCreateItemRev, "object_desc", cItemN));
				}
				else
				{
					ITK(AOM_set_value_string(tCreateItem, "object_desc", cItemDesc));
					ITK(AOM_set_value_string(tCreateItemRev, "object_desc", cItemDesc));
				}
			}
			else
			{
				ITK(AOM_set_value_string(tCreateItem, "object_desc", cItemN));
				ITK(AOM_set_value_string(tCreateItemRev, "object_desc", cItemN));
			}

			ITK(AOM_set_value_string(tCreateItemRev, "object_name", cItemName));
			
			ITK(AOM_set_value_string(tCreateItemRev, "item_revision_id", cRevID));

			ITK( AOM_set_value_tag(tCreateItem, "revision", tCreateItemRev) );
			ITK(TCTYPE_create_object( tCreateItem, &tItem ));

			logger.writebothlog("\nProcessing for DTDocumentItem and DTDocumentRevision with ID : " + string(cItemID) + " and Revision : " + cRevID);

			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);

				logger.writebothlog("Creation of DTDocumentItem and DTDocumentRevision with ID : " + string(cItemID) + " and Revision : " + cRevID + " is failed error code : " + IntToString(status) + " : " + error);
				//staging db updation
				iTCProcessStatus = 2;
				status = dbObj.update_table_doc(cItemID,cRevID,iTCProcessStatus,NULL,cFileOrigName);
				if(status != ITK_ok)
				{
					logger.writebothlog("ERROR: Unable to Login to Database");
				}
				else
				{
					logger.write("Staging Database WC2TC_DOCUMENT Updation with TC_PROCESS_STATUS and TC_PROCESSDATE and TC_GROUP is successful");
				}

				return NULL;
			}
			else
			{
				logger.write( "Setting properties for DTDocument ...");
			}

			ITEM_save_item(tItem);

			POM_set_env_info(POM_bypass_attr_update, FALSE, 0, 0, NULLTAG, NULL);

			findItemRev(sTCItemID.c_str(), cRevID, tItemRev);

		if (tItemRev!=NULLTAG)
		{

			//creation and modification
			//string sCreationDate	= ConvertDate_To_TCFormat(cCreationDate);
			//ITK(ITK_string_to_date(sCreationDate.c_str(),&dtCreationDate));

			string sCreationDate	= ConvertDate_To_TCFormat_rev(cCreationDate,cRevID);
			logical  	date_is_valid ;
			ITK(DATE_string_to_date_t((char*) sCreationDate.c_str(),&date_is_valid,&dtCreationDate ));		


			string sModDate		= ConvertDate_To_TCFormat(cModDate);
			ITK(ITK_string_to_date(sModDate.c_str(),&dtLastModDate));	

			//release date
			string sRelDate	= ConvertDate_To_TCFormat(cRelDate);
			ITK(ITK_string_to_date(sRelDate.c_str(),&dtRelDate));

			iTCProcessStatus = setuseranddate(tItem , cCreatedBy, cLastModBy , dtCreationDate, dtLastModDate ,  sCreationDate, sModDate , iTCProcessStatus);
			iTCProcessStatus = setuseranddate(tItemRev , cCreatedBy, cLastModBy , dtCreationDate, dtLastModDate ,  sCreationDate, sModDate , iTCProcessStatus);

			//form attributes
			iTCProcessStatus = setFormAttributes(tItem,cCustSuplNo,tOwner, dtCreationDate,dtLastModDate,tModifiedBy,sReleaseStatus , dtRelDate, cReferenceRevision,iTCProcessStatus);
			ITEM_save_item(tItem);

			//tItemRev IMAN_master_form_rev
			iTCProcessStatus = setFormAttributes(tItemRev,cCustSuplNo,tOwner, dtCreationDate,dtLastModDate,tModifiedBy,sReleaseStatus , dtRelDate ,cReferenceRevision,iTCProcessStatus);

			//preserve windchill Name
			/*ITK(AOM_set_value_string(tItemRev,"bwr3_DT_Doc_Rev_Comments",cItemN));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error : Preserving Windchill Item name : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}*/

			AOM_refresh(tItemRev,true);

			ITK(POM_attr_id_of_attr("date_released", "WorkspaceObject", &attr_id_dateRel));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error : Getting attribute id of release date : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				ITK(POM_set_attr_date(1,&tItemRev,attr_id_dateRel, dtRelDate));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Fail | Release date | " + sRelDate + " : error code : " + IntToString(status) + " : " + error );
					iTCProcessStatus = 2;
				}
				else
				{
					logger.writeattributelog("Release date" , sRelDate );
				}
			}

			tag_t tRelStatus = NULLTAG;
				int iNDStatuslist = 0;
				tag_t *tNDStatuslist = NULL;
				ITK(WSOM_ask_release_status_list(tItemRev,&iNDStatuslist,&tNDStatuslist));
				if(iNDStatuslist == 0)
				{	 
					if(tc_strcmp(sReleaseStatus.c_str(),"")!=0)
					{
	 					ITK(RELSTAT_create_release_status(sReleaseStatus.c_str(),&tRelStatus));
						ITK(RELSTAT_add_release_status(tRelStatus,1,&tItemRev,TRUE));
						if(status!=ITK_ok)
						{
							char * error = NULL;
							EMH_ask_error_text(status , &error);
							logger.writebothlog("Fail | Release Status Form | " + sReleaseStatus + " : error code : " + IntToString(status) + " : " + error );
							iTCProcessStatus	=	2;
						}
						else
						{
							logger.writeattributelog("Release Status Form" , sReleaseStatus );
						}
					}
				}
				SAFE_MEM_FREE(tNDStatuslist);
			
			logger.writebothlog("Processing of datasets for document with ID " + string(cItemID) + " and Revision " + cRevID + "....");
			
			int Fail = createDataset(tItemRev,cItemID , cRevID , cCreatedBy,cLastModBy,dtCreationDate,dtLastModDate,dtRelDate,sCreationDate,sModDate,sRelDate,sReleaseStatus , iTCProcessStatus);
			
			ITEM_save_item(tItem); 
			ITEM_save_rev(tItemRev);

			if( Fail == 2 )
            {
                logical state_has_changed = FALSE;
                if(status = POM_roll_to_markpoint( myPOMMark, &state_has_changed ) == ITK_ok)
                {
					logger.writebothlog("Creation of DTDocument with ID " + string(cItemID) + " and Revision " + cRevID + " is Failed");		
                }
				else
				{
					logger.write(IntToString(status) + " : POM_roll_to_markpoint is failed");
				}
            }
            else
            {                                              
				POM_forget_markpoint( myPOMMark ) ;
				logger.writebothlog("Creation of DTDocumentItem with ID : \t " + string(cItemID) + " and Revision " + cRevID + " is Successful\n");
			}


			POM_set_env_info(POM_bypass_attr_update, TRUE, 0, 0, NULLTAG, NULL);
		 }//if(tItemRev == NULL)

		}//if(tItem == NULL)
		else			//item is present but item revision is not present
		{
			findItemRev(sTCItemID.c_str(), cRevID, tItemRev);
			//get owning user
			tag_t owning_user = NULLTAG;
			ITK(AOM_ask_owner(tItem,&owning_user));
			char * cOwnerName = NULL;
			if(owning_user!=NULLTAG)
			{
				ITK(POM_ask_user_id(owning_user,&cOwnerName));
				if(status!=ITK_ok)
				{
					ITK(AOM_refresh(owning_user, true));
					ITK(POM_ask_user_id(owning_user,&cOwnerName));
					ITK(AOM_refresh(owning_user, false));
				}
			}
			string sWCowner = getWCUser(cOwnerName);

			//if(tItemRev==NULL && tc_strcmp(cOwnerName,"bw_mig")==0)
			if(tItemRev==NULL && (tc_strcmp(cOwnerName,"bw_mig")==0 || tc_strcmp(sWCowner.c_str(),cCreatedBy)==0 || tc_strcmp(cDelta,"YES")==0 )	)
			{
				int myPOMMark = 0;
				if (status = POM_place_markpoint( &myPOMMark ) != ITK_ok)
				{
					logger.write(IntToString(status) + "POM-place-markpoint");
				}

				ITK(TCTYPE_construct_create_input	( tDTDocumentRevType, &tCreateItemRev ));

				ITK(AOM_set_value_string(tCreateItemRev, "object_name", cItemName));
				if( tc_strcmp(cItemDesc, "") != 0)
				{
				string sItemDesc(cItemDesc);
				transform(sItemDesc.begin(), sItemDesc.end(), sItemDesc.begin(),(int (*)(int))tolower);

				if(tc_strcmp(sItemDesc.c_str(),"null") == 0)
				{
					
					ITK(AOM_set_value_string(tCreateItemRev, "object_desc", cItemN));
				}
					else
					{
						
						ITK(AOM_set_value_string(tCreateItemRev, "object_desc", cItemDesc));
					}
				}
			else
			{
				
				ITK(AOM_set_value_string(tCreateItemRev, "object_desc", cItemN));
			}


				ITK(AOM_set_value_string(tCreateItemRev, "item_revision_id", cRevID));

				ITK(AOM_set_value_tag(tCreateItemRev, "items_tag", tItem));

				ITK(TCTYPE_create_object( tCreateItemRev, &tItemRev ));

				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Creation of DTDocumentRevision  with ID : " + string(cItemID) + " and Revision : " + cRevID + " is failed error code : " + IntToString(status) + " : " + error);

					//staging db updation
					iTCProcessStatus = 2;
					status = dbObj.update_table_doc(cItemID,cRevID,iTCProcessStatus,NULL,cFileOrigName);
					if(status != ITK_ok)
					{
						logger.writebothlog( "ERROR: Unable to Login to Database");
					}
					else
					{
						logger.write("Staging Database WC2TC_DOCUMENT Updation with TC_PROCESS_STATUS and TC_PROCESSDATE and TC_GROUP is successful");
					}

					return NULL;
				}
				else
				{
					//logger.write( "Creation of DTDocumentRevision created for ID : " + string(cItemID) + " and Revision : " + cRevID+ " is successful");
					logger.write("Setting properties for DTDocument ...");
				}

				
				ITEM_save_rev(tItemRev);

				POM_set_env_info(POM_bypass_attr_update, FALSE, 0, 0, NULLTAG, NULL);
				

				//creation and modification
				//string sCreationDate	= ConvertDate_To_TCFormat(cCreationDate);
				//ITK(ITK_string_to_date(sCreationDate.c_str(),&dtCreationDate));
				string sCreationDate	= ConvertDate_To_TCFormat_rev(cCreationDate,cRevID);
				logical  	date_is_valid ;
				ITK(DATE_string_to_date_t((char*) sCreationDate.c_str(),&date_is_valid,&dtCreationDate ));

				string sModDate		= ConvertDate_To_TCFormat(cModDate);
				ITK(ITK_string_to_date(sModDate.c_str(),&dtLastModDate));	

				//convertToTCDate(cRelDate,dtRelDate);
				string sRelDate	= ConvertDate_To_TCFormat(cRelDate);
				ITK(ITK_string_to_date(sRelDate.c_str(),&dtRelDate));

				iTCProcessStatus = setuseranddate(tItemRev , cCreatedBy, cLastModBy , dtCreationDate, dtLastModDate ,  sCreationDate, sModDate , iTCProcessStatus);

				//last modified date on item
				ITK( AOM_refresh(tItem, TRUE) );
				ITK(POM_set_modification_date(tItem, dtLastModDate));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog( "Fail | Modification date on item | " + sModDate + " : error code : " + IntToString(status) + " : " + error );
					iTCProcessStatus	=	2;
				}
				else
				{
					logger.writeattributelog( "Modification date on item" , sModDate );
				}

				iTCProcessStatus = setFormAttributes(tItem,cCustSuplNo,tOwner, dtCreationDate,dtLastModDate,tModifiedBy,sReleaseStatus , dtRelDate,cReferenceRevision,iTCProcessStatus);

				ITEM_save_item(tItem); 
				ITK( AOM_refresh(tItem, FALSE) );

				
				ITK(AOM_refresh(tItemRev, TRUE));
					
				//tItemRev IMAN_master_form_rev
				iTCProcessStatus = setFormAttributes(tItemRev,cCustSuplNo,tOwner, dtCreationDate,dtLastModDate,tModifiedBy,sReleaseStatus , dtRelDate,cReferenceRevision,iTCProcessStatus);

				//release date
				ITK(POM_attr_id_of_attr("date_released", "WorkspaceObject", &attr_id_dateRel));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog( "Error : Getting attribute id of release date : " + IntToString(status) + " : " + error );
					iTCProcessStatus	=	2;
				}
				else
				{
					ITK(POM_set_attr_date(1,&tItemRev,attr_id_dateRel, dtRelDate));
					if(status!=ITK_ok)
					{
						char * error = NULL;
						EMH_ask_error_text(status , &error);
						logger.writebothlog( "Release date : " + sRelDate + " : error code : " + IntToString(status) + " : " + error );
						iTCProcessStatus = 2;

					}
					else
					{
						logger.writeattributelog( "Release date" , sRelDate );
					}
				}

				tag_t tRelStatus = NULLTAG;
				int iNDStatuslist = 0;
				tag_t *tNDStatuslist = NULL;
				ITK(WSOM_ask_release_status_list(tItemRev,&iNDStatuslist,&tNDStatuslist));
				if(iNDStatuslist == 0)
				{	 
					if(tc_strcmp(sReleaseStatus.c_str(),"")!=0)
					{
	 					ITK(RELSTAT_create_release_status(sReleaseStatus.c_str(),&tRelStatus));
						ITK(RELSTAT_add_release_status(tRelStatus,1,&tItemRev,TRUE));
						if(status!=ITK_ok)
						{
							char * error = NULL;
							EMH_ask_error_text(status , &error);
							logger.writebothlog("Fail | Release Status Form | " + sReleaseStatus + " : error code : " + IntToString(status) + " : " + error );
							iTCProcessStatus	=	2;
						}
						else
						{
							logger.writeattributelog("Release Status Form" , sReleaseStatus );
						}
					}
				}
				SAFE_MEM_FREE(tNDStatuslist);

				logger.writebothlog("Processing of datasets for document with ID " + string(cItemID) + " and Revision " + cRevID + "....");
				int Fail = createDataset(tItemRev,cItemID , cRevID , cCreatedBy,cLastModBy,dtCreationDate,dtLastModDate,dtRelDate,sCreationDate,sModDate,sRelDate,sReleaseStatus , iTCProcessStatus);
				
				ITEM_save_rev(tItemRev);
				if( Fail == 2 )
				{
					logical state_has_changed = FALSE;
					if(status = POM_roll_to_markpoint( myPOMMark, &state_has_changed ) == ITK_ok)
					{
						logger.writebothlog("Creation of DTDocument with ID " + string(cItemID) + " and Revision " + cRevID + " is Failed");
						//logger.writeEmaillogFailed("Creation of DTDocumentItem with ID : \t " + string(cItemID) + " and Revision " + cRevID + " is Failed\n");
					}
					else
					{
						logger.write(IntToString(status) + " : POM_roll_to_markpoint is failed");
					}
				}
				else
				{                                              

					POM_forget_markpoint( myPOMMark ) ;
					logger.writebothlog("Creation of DTDocumentItem with ID : \t " + string(cItemID) + " and Revision " + cRevID + " is Successful\n");
					//logger.writemaillog("Creation of DTDocumentItem with ID : \t " + string(cItemID) + " and Revision " + cRevID + " is Successful\n");
				}

				POM_set_env_info(POM_bypass_attr_update, TRUE, 0, 0, NULLTAG, NULL);

			}//if(tItemRev==NULL)
			else
			{
				//if(tc_strcmp(cOwnerName,"bw_mig")!=0)
				if(	tc_strcmp(cOwnerName,"bw_mig")!=0 && tc_strcmp(cDelta,"No")==0	)	
				{
					logger.write("DTDocument with ID " + string(cItemID) +" is already present in Teamcenter with owner " + cOwnerName + " Please contact administrator for further procedure...");
					//set status to 11 present with another user
					dbObj.update_table_doc(cItemID,cRevID,11,NULL,cFileOrigName);
					tItemRev = NULLTAG;
				}
				else
				{
					logger.write("DTDocument with ID " + string(cItemID) + " and Revision " + cRevID + " is already present in Teamcenter...");
					if(tc_strcmp(cDelta,"YES")==0)
					{
						int myPOMMark = 0;
						if (status = POM_place_markpoint( &myPOMMark ) != ITK_ok)
						{
							logger.write(IntToString(status) + "POM-place-markpoint");
						}

						POM_set_env_info(POM_bypass_attr_update, FALSE, 0, 0, NULLTAG, NULL);

						//creation and modification
						string sCreationDate	= ConvertDate_To_TCFormat_rev(cCreationDate,cRevID);
						
						logical  	date_is_valid ;
						ITK(DATE_string_to_date_t((char*) sCreationDate.c_str(),&date_is_valid,&dtCreationDate ));

						string sModDate		= ConvertDate_To_TCFormat(cModDate);
						ITK(ITK_string_to_date(sModDate.c_str(),&dtLastModDate));	

						//convertToTCDate(cRelDate,dtRelDate);
						string sRelDate	= ConvertDate_To_TCFormat(cRelDate);
						ITK(ITK_string_to_date(sRelDate.c_str(),&dtRelDate));

						iTCProcessStatus = setuseranddate(tItemRev , cCreatedBy, cLastModBy , dtCreationDate, dtLastModDate ,  sCreationDate, sModDate , iTCProcessStatus);

						//last modified date on item
						ITK( AOM_refresh(tItem, TRUE) );
						ITK(POM_set_modification_date(tItem, dtLastModDate));
						if(status!=ITK_ok)
						{
							char * error = NULL;
							EMH_ask_error_text(status , &error);
							logger.writebothlog( "Fail | Modification date on item | " + sModDate + " : error code : " + IntToString(status) + " : " + error );
							iTCProcessStatus	=	2;
						}
						else
						{
							logger.writeattributelog( "Modification date on item" , sModDate );
						}

						iTCProcessStatus = setFormAttributes(tItem,cCustSuplNo,tOwner, dtCreationDate,dtLastModDate,tModifiedBy,sReleaseStatus , dtRelDate,cReferenceRevision,iTCProcessStatus);

						ITEM_save_item(tItem); 
						ITK( AOM_refresh(tItem, FALSE) );

				
						ITK(AOM_refresh(tItemRev, TRUE));
					
						//tItemRev IMAN_master_form_rev
						iTCProcessStatus = setFormAttributes(tItemRev,cCustSuplNo,tOwner, dtCreationDate,dtLastModDate,tModifiedBy,sReleaseStatus , dtRelDate,cReferenceRevision,iTCProcessStatus);

						//release date
						ITK(POM_attr_id_of_attr("date_released", "WorkspaceObject", &attr_id_dateRel));
						if(status!=ITK_ok)
						{
							char * error = NULL;
							EMH_ask_error_text(status , &error);
							logger.writebothlog( "Error : Getting attribute id of release date : " + IntToString(status) + " : " + error );
							iTCProcessStatus	=	2;
						}
						else
						{
							ITK(POM_set_attr_date(1,&tItemRev,attr_id_dateRel, dtRelDate));
							if(status!=ITK_ok)
							{
								char * error = NULL;
								EMH_ask_error_text(status , &error);
								logger.writebothlog( "Release date : " + sRelDate + " : error code : " + IntToString(status) + " : " + error );
								iTCProcessStatus = 2;

							}
							else
							{
								logger.writeattributelog( "Release date" , sRelDate );
							}
						} //end of else

						tag_t tRelStatus = NULLTAG;
						int iNDStatuslist = 0;
						tag_t *tNDStatuslist = NULL;
						ITK(WSOM_ask_release_status_list(tItemRev,&iNDStatuslist,&tNDStatuslist));
						if(iNDStatuslist == 0)
						{	 
							if(tc_strcmp(sReleaseStatus.c_str(),"")!=0)
							{
	 							ITK(RELSTAT_create_release_status(sReleaseStatus.c_str(),&tRelStatus));
								ITK(RELSTAT_add_release_status(tRelStatus,1,&tItemRev,TRUE));
								if(status!=ITK_ok)
								{
									char * error = NULL;
									EMH_ask_error_text(status , &error);
									logger.writebothlog("Fail | Release Status Form | " + sReleaseStatus + " : error code : " + IntToString(status) + " : " + error );
									iTCProcessStatus	=	2;
								}
								else
								{
									logger.writeattributelog("Release Status Form" , sReleaseStatus );
								}
							}
						}
						SAFE_MEM_FREE(tNDStatuslist);

						logger.writebothlog("Processing of datasets for document with ID " + string(cItemID) + " and Revision " + cRevID + "....");
								
						//delete current datasets
						tag_t tRelation = NULLTAG;
						tag_t tRelType = NULLTAG; 
						ITK( GRM_find_relation_type("IMAN_specification", &tRelType) );

						int iCntIRSecObj = 0;
						tag_t * tIRSecObj = NULL;

						ITK( GRM_list_secondary_objects_only(tItemRev, tRelType, &iCntIRSecObj, &tIRSecObj) );
						for(int i = 0; i < iCntIRSecObj; i++)
						{
							tRelation = NULLTAG;
							ITK( GRM_find_relation(tItemRev,tIRSecObj[i],tRelType, &tRelation) );
							if ( tRelation != NULLTAG )
							{
								ITK( GRM_delete_relation( tRelation ) );
							}
							// Remove the dataset & the file, by their tags 
							if ( tIRSecObj[i] != NULLTAG )
							{
								ITK( AOM_lock_for_delete( tIRSecObj[i] ) );
								ITK( AOM_delete( tIRSecObj[i]) );
							}
						}
						SAFE_MEM_FREE(tIRSecObj);
						ITEM_save_rev(tItemRev);
						ITK(AOM_refresh(tItemRev, FALSE));

						ITK(AOM_refresh(tItemRev, TRUE));

						int Fail = createDataset(tItemRev,cItemID , cRevID , cCreatedBy,cLastModBy,dtCreationDate,dtLastModDate,dtRelDate,sCreationDate,sModDate,sRelDate,sReleaseStatus , iTCProcessStatus);
				
						ITEM_save_rev(tItemRev);
						ITK(AOM_refresh(tItemRev, FALSE));
						if( Fail == 2 )
						{
							logical state_has_changed = FALSE;
							if(status = POM_roll_to_markpoint( myPOMMark, &state_has_changed ) == ITK_ok)
							{
								//logger.write(IntToString(status) + "POM_roll_to_markpoint");
								logger.writebothlog("Creation of DTDocument with ID " + string(cItemID) + " and Revision " + cRevID + " is Failed");
								////logger.writemaillog("Creation of DTDocumentItem with ID : \t " + string(cItemID) + " and Revision " + cRevID + " is Failed\n");
							}
							else
							{
								logger.write(IntToString(status) + " : POM_roll_to_markpoint is failed");
							}
							tItemRev = NULLTAG;
						}
						else
						{                                              
							POM_forget_markpoint( myPOMMark ) ;
							logger.writebothlog("Creation of DTDocument with ID " + string(cItemID) + " and Revision " + cRevID + " is Successful");
							////logger.writemaillog("Creation of DTDocumentItem with ID : \t " + string(cItemID) + " and Revision " + cRevID + " is Successful\n");
						}
						POM_set_env_info(POM_bypass_attr_update, TRUE, 0, 0, NULLTAG, NULL);
					}
				}
			}

		}////item is present but item revision is not present

	}//if(tc_strcmp(cMigrationType,"0") == 0 && tc_strcmp(cMigrationDes,"0") == 0)
	else
	{
		/*if(tc_strcmp(cMigrationDes,"0") != 0)
		{
			logger.writebothlog("Document with id : " + string(cItemID) + " and Revision: " + cRevID + " is not ready for Migration");
		}
		else if(tc_strcmp(cTCProcessStatus,"1") == 0)
		{
			logger.writebothlog("Document with id : " + string(cItemID) + " and Revision: " + cRevID + " is already present in teamcenter");
		}*/
	}

	return tItemRev;
	
}

/******************************************************************************************************************************************
Function    : setFormAttributes(tag_t tItemRev,char * cCustSuplNo , tag_t tOwner, date_t	dtCreationDate , date_t	dtLastModDate , 
			  tag_t tModifiedBy ,string sReleaseStatus,date_t dtRelDate , int iTCProcessStatus)
Description : Receives the Item/Item Revision tag and set attributes to corresponding Master forms and also some relevant forms.

******************************************************************************************************************************************/
int BW_DocInjector::setFormAttributes(tag_t tItemRev,char * cCustSuplNo , tag_t tOwner, date_t	dtCreationDate , date_t	dtLastModDate , tag_t tModifiedBy , string sReleaseStatus,date_t dtRelDate , char * cRefRevision,int iTCProcessStatus)
{
	int			status				= ITK_ok;
	tag_t		relation_type		= NULLTAG;
	tag_t*		secondary_objects	= NULL;
	int 		count				= 0;
	

	ITK(GRM_find_relation_type("IMAN_master_form_rev",&relation_type));
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		//cout << status << " : "<< error << endl;
	}
	GRM_list_secondary_objects_only (tItemRev,relation_type,&count,&secondary_objects);
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		logger.writebothlog("Error while getting secondary objects of item : error code : " + IntToString(status) + " : " + error );
	}
	
	for(int inx=0; inx < count; inx++ )
	{
		char * ObjType = NULL;
		ITK( AOM_ask_value_string(secondary_objects[inx], "object_type", &ObjType));
		if(tc_strcmp(ObjType,"DT_Document Revision Master")==0)
		{

			ITK(AOM_refresh(secondary_objects[inx],TRUE));
			
			//creation date and user
			/*ITK(POM_set_owning_user(secondary_objects[inx], tOwner));			
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Owning User on Revision Master Form | error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Owning User on Revision Master Form ");
			}*/


			ITK(POM_set_creation_date(secondary_objects[inx], dtCreationDate));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Creation date on Revision Master Form | error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Creation date on Revision Master Form ");
			}

			//modification date and user
			ITK(POM_set_modification_date(secondary_objects[inx], dtLastModDate));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Modification date on Revision Master Form : error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Modification date on Revision Master Form ");
			}
			/*ITK(POM_set_modification_user(secondary_objects[inx], tModifiedBy));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Last Modification User on Revision Master Form : error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Last Modification User on Revision Master Form ");
			}*/

			ITK(AOM_set_value_string(secondary_objects[inx], "DT_migration_status", "Yes"));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Fail | DT Migration Status on Item revision master form | Yes : error code : " + IntToString(status) + " : " + error );
			}
			else
			{
				logger.writeattributelog("DT Migration Status on Item revision master form", "Yes" );
			}
			ITK(AOM_set_value_string(secondary_objects[inx], "bwr3_re_reference_revision", cRefRevision));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Fail | Reference Revision on Item revision master form | " + string(cRefRevision) + " : error code : " + IntToString(status) + " : " + error );
			}
			else
			{
				logger.writeattributelog("Reference Revision on Item revision master form", string(cRefRevision) );
			}
			

			//release date
			tag_t attr_id_dateRel = NULLTAG;
			ITK(POM_attr_id_of_attr("date_released", "WorkspaceObject", &attr_id_dateRel));					//Dataset Release Date
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error : Getting attribute id of release date : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				ITK(POM_set_attr_date(1,&secondary_objects[inx],attr_id_dateRel, dtRelDate));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					//logger.writebothlog("Fail | Release date | " + sRelDate + " : error code : " + IntToString(status) + " : " + error );
					iTCProcessStatus = 2;
				}
				else
				{
					//logger.writeattributelog("Release date Dataset" ,  sModDate);
				}
			}

			tag_t tRelStatus = NULLTAG;
				int iNDStatuslist = 0;
				tag_t *tNDStatuslist = NULL;
				ITK(WSOM_ask_release_status_list(secondary_objects[inx],&iNDStatuslist,&tNDStatuslist));
				if(iNDStatuslist == 0)
				{	 
					if(tc_strcmp(sReleaseStatus.c_str(),"")!=0)
					{
	 					ITK(RELSTAT_create_release_status(sReleaseStatus.c_str(),&tRelStatus));
						ITK(RELSTAT_add_release_status(tRelStatus,1,&secondary_objects[inx],TRUE));
						if(status!=ITK_ok)
						{
							char * error = NULL;
							EMH_ask_error_text(status , &error);
							logger.writebothlog("Fail | Release Status Form | " + sReleaseStatus + " : error code : " + IntToString(status) + " : " + error );
							iTCProcessStatus	=	2;
						}
						else
						{
							logger.writeattributelog("Release Status Form" , sReleaseStatus );
						}
					}
				}
				SAFE_MEM_FREE(tNDStatuslist);
			
			ITK(AOM_save(secondary_objects[inx]));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog( "Error while saving Item revision master form : error code : " + IntToString(status) + " : " + error );
			}
			//ITK(AOM_save(tItemRev));
			ITK(AOM_refresh(secondary_objects[inx],FALSE));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
			}
			break;
		
		}
		else if(tc_strcmp(ObjType,"DT_Document Master")==0)	//item master for master
		{

			ITK(AOM_refresh(secondary_objects[inx],TRUE));

			//creation date and user
			/*ITK(POM_set_owning_user(secondary_objects[inx], tOwner));	
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Owning User on Revision Master Form | error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Owning User on Revision Master Form ");
			}*/

			ITK(POM_set_creation_date(secondary_objects[inx], dtCreationDate));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Creation date on Revision Master Form | error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Creation date on Revision Master Form ");
			}

			//modification date and user
			ITK(POM_set_modification_date(secondary_objects[inx], dtLastModDate));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Modification date on Revision Master Form : error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Modification date on Revision Master Form ");
			}
			/*ITK(POM_set_modification_user(secondary_objects[inx], tModifiedBy));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writefaillog("Fail | Last Modification User on Revision Master Form : error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				//logger.write("Pass | Last Modification User on Revision Master Form ");
			}*/

			//lov
			char		*s_CustSuplvalue[1]	;
			s_CustSuplvalue[0] = cCustSuplNo;

			char		*s_BusinessGrpvalue[1]	;
			s_BusinessGrpvalue[0] = "PDS";

			char		*s_LocationSitevalue[1]	;
			s_LocationSitevalue[0] = "ITC";

			//
			ITK(AOM_set_value_strings(secondary_objects[inx], "bwr3_re_business_group", 1 , s_BusinessGrpvalue));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Fail | Business group on Item Master | " + string(s_BusinessGrpvalue[0]) + " error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus		= 2;
			}
			else
			{
				logger.writeattributelog("Business group on Item Master" , string(s_BusinessGrpvalue[0]) );
			}

			ITK(AOM_set_value_strings(secondary_objects[inx], "bwr3_re_loc_design_site", 1 , s_LocationSitevalue));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Fail | Location Site on Item Master | " + string(s_LocationSitevalue[0]) + " error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus		= 2;
			}
			else
			{
				logger.writeattributelog("Location Site on Item Master" , string(s_LocationSitevalue[0]) );
			}

			ITK(AOM_set_value_strings(secondary_objects[inx], "bwr3_DT_AlternatePartNumber", 1 , s_CustSuplvalue));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Fail | Customer supplier number on Item Master | " + string(cCustSuplNo) + " error code : " + IntToString(status) + " : " + error);
				iTCProcessStatus		= 2;
			}
			else
			{
				logger.writeattributelog("Customer supplier number on Item Master" , string(cCustSuplNo) );
			}

			
			ITK(AOM_save(secondary_objects[inx]));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.write( "Error while saving Item master form : error code : " + IntToString(status) + " : " + error );

			}
			//ITK(AOM_save(tItemRev));
			ITK(AOM_refresh(secondary_objects[inx],FALSE));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
			}
			break;
		}
	}
	if(secondary_objects!=NULL)
		SAFE_MEM_FREE(secondary_objects);
	return 	iTCProcessStatus;;
}

/******************************************************************************************************************************************
Function    : createDataset(tag_t tRev, char* cFileName, char* cFilePath, char* cFileType, tag_t& tDataset , int iTCProcessStatus)
Description : Creates the dataset using Filetype and attach namedreference to it andattach it with corresponding ItemRevision 

******************************************************************************************************************************************/

int BW_DocInjector::createDataset(tag_t tRev, char* cItemId,char* cRevID,char *cCreatedBy,char *cLastModBy,date_t dtCreationDate ,date_t dtLastModDate,date_t dtRelDate,string sCreationDate,string sModDate,
	string sRelDate , string sReleaseStatus, int iTCProcessStatus)
{
	int status = ITK_ok;

	int Fail = 1;

	string allFilesQuery = "SELECT DISTINCT [FILE_ORIGINAL_NAME],[FILE_PATH],[FILE_TYPE] FROM [WC2TC_DOCUMENT_PHASED] WHERE DOCUMENTNUMBER = '";
	allFilesQuery += cItemId;	allFilesQuery += "' AND DOCUMENTREVISION = '";	allFilesQuery += cRevID;	allFilesQuery += "'";

	vector<string> AllRows = dbObj.executeQuery(allFilesQuery,3);

	for(int inx=0;inx<AllRows.size();inx++)
	{
		string row = AllRows.at(inx);

		char *	cFileName			=	tc_strtok ((char *)row.c_str(), "!");
		char *	cFilePath			=	tc_strtok (NULL, "!");
		char *	cFileType			=	tc_strtok (NULL, "!");
	
		char format_name[AE_io_format_size_c + 1] = "BINARY_REF";
	
		tag_t		tDataset			=	NULLTAG;
		tag_t		tDatasetType		=	NULLTAG;
		tag_t		tRelType			=	NULLTAG;
		tag_t		tRelation			=	NULLTAG;
		tag_t		tFileTag			=	NULLTAG;
		IMF_file_t  fileDescriptor		=	NULL;
   
		string	sFileName = cFileName;
		if(sFileName.find_last_of(".")!=std::string::npos)
		{
			size_t pos = sFileName.find_last_of(".");      // position of "live" in str
			sFileName = sFileName.substr (0,pos);
		}

		string sFileType = TypeToDtsMap(cFileType);
		if(tc_strcmp(cFileType,"No Content")!=0)
		{
			ITK( AE_find_datasettype2(sFileType.c_str() , &tDatasetType) );
			ITK( AE_create_dataset_with_id(  tDatasetType, sFileName.c_str(), cFileName, 0, 0, &tDataset) );
			if(status==ITK_ok)
			{
				logger.write("\nDataset creation with name : " + string(cFileName) + " is Successful" );
			}
			else
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("\nDataset creation with name : " + string(cFileName) + " is failed, Error code : " + IntToString(status) + " : " + error);
				iTCProcessStatus = 2;
			}

			string sRefType = TypeToRefMap(cFileType);
			string sTransform = cFileType;
			transform(sTransform.begin(), sTransform.end(), sTransform.begin(),(int (*)(int))tolower);
			if(tc_strcmp( sTransform.c_str(), "txt" )==0 || tc_strcmp( sTransform.c_str(), "pwd" )==0 || tc_strcmp(sTransform.c_str(), "stp" )==0 || tc_strcmp(sTransform.c_str(), "mdi" )==0)
			{
				ITK(AE_set_dataset_format2(tDataset, "TEXT_REF"));
				ITK(AE_import_named_ref(tDataset, TypeToRefMap(cFileType).c_str() ,cFilePath, NULL, SS_TEXT));
				string sFielpath  = cFilePath;
				if(status!=ITK_ok)
				{
						char * error = NULL;
						EMH_ask_error_text(status , &error);
						if(tc_strcmp(error,"File %1$s does not exist")==0)
						{
							size_t pos = 0;
							while(sFielpath.find('/',pos+2) != string::npos)
							{
								pos = sFielpath.find('/', pos+2);
								sFielpath.replace(pos, 1, "\\");
							}
							ITK(AE_import_named_ref(tDataset, TypeToRefMap(cFileType).c_str(), (char*)sFielpath.c_str(), NULL, SS_TEXT));
							if(status!=ITK_ok)
							{								
								EMH_ask_error_text(status , &error);
								iTCProcessStatus = 2;
								logger.writebothlog("Fail | Dataset is not attached to item revision | Error code : " + IntToString(status) + " : " + error );
								Fail=2;
								
							}
						}

						else
						{
							iTCProcessStatus = 2;
							logger.writebothlog("Fail | Dataset is not attached to item revision | Error code : " + IntToString(status) + " : " + error );
							Fail=2;
						}
				}
				else
				{
					logger.writeattributelog("Named Reference attached to Dataset " ,  string(cFileName) );
				}
			}
			else
			{
				ITK(AE_set_dataset_format2(tDataset, format_name));
				ITK(AE_import_named_ref(tDataset, TypeToRefMap(cFileType).c_str() ,cFilePath, NULL, SS_BINARY));
				string sFielpath  = cFilePath;
				if(status!=ITK_ok)
				{
						char * error = NULL;
						EMH_ask_error_text(status , &error);
						if(tc_strcmp(error,"File %1$s does not exist")==0)
						{
							size_t pos = 0;
							while(sFielpath.find('/',pos+2) != string::npos)
							{
								pos = sFielpath.find('/', pos+2);
								sFielpath.replace(pos, 1, "\\");
							}
							ITK(AE_import_named_ref(tDataset, TypeToRefMap(cFileType).c_str(), (char*)sFielpath.c_str(), NULL, SS_TEXT));
							if(status!=ITK_ok)
							{								
								EMH_ask_error_text(status , &error);
								iTCProcessStatus = 2;
								logger.writebothlog("Fail | Dataset is not attached to item revision | Error code : " + IntToString(status) + " : " + error );
								Fail=2;
								
							}
						}

						else
						{
							iTCProcessStatus = 2;
							logger.writebothlog("Fail | Dataset is not attached to item revision | Error code : " + IntToString(status) + " : " + error );
							Fail=2;
						}
				}
				else
				{
					logger.writeattributelog("Named Reference attached to Dataset " ,  string(cFileName) );
				}
			}
			ITK(AOM_save(tDataset));

			ITK( GRM_find_relation_type("IMAN_specification", &tRelType) );
			ITK( GRM_create_relation	(tRev, tDataset, tRelType, NULLTAG, &tRelation) );
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				iTCProcessStatus = 2;
				logger.writebothlog("Fail | Dataset is not attached to item revision | Error code : " + IntToString(status) + " : " + error );
			}
			ITK( AOM_save(tRelation) );
		}
		//set properties
		if(tDataset != NULL)
		{
				iTCProcessStatus = setDatasetAttributes(tDataset,cCreatedBy,cLastModBy,dtCreationDate,dtLastModDate,dtRelDate,sCreationDate,sModDate,sRelDate,sReleaseStatus , iTCProcessStatus);
		}
		//for mail
		if(iTCProcessStatus==1)
		{
			//logger.writemaillog("Creation of DTDocumentItem with ID : \t " + string(cItemId) + " and Revision " + cRevID + " is Suceessful\n");
		}
		else
		{
			//logger.writemaillog("Creation of DTDocumentItem with ID : \t " + string(cItemId) + " and Revision " + cRevID + " is Failed\n");
			Fail=2;
		}
		//update DB
		int iStatus = dbObj.update_table_doc(cItemId,cRevID,iTCProcessStatus,"dba",cFileName);
		if(iStatus != ITK_ok)
		{
			logger.writebothlog( "ERROR: Unable to Login to Database");
		}
		else
		{
			logger.write("Staging Database WC2TC_DOCUMENT Updation with TC_PROCESS_STATUS and TC_PROCESSDATE with id : " + string(cItemId) + " ,Revision : " + cRevID + " And File : " + cFileName + " is successful ");
		}
	}
	if(Fail==2)
	{
		//update DB
		int iStatus = dbObj.update_table_Fail(cItemId,cRevID);
		if(iStatus != ITK_ok)
		{
			logger.writebothlog( "ERROR: Unable to Login to Database");
		}
		
	}
	return Fail;
	
}

/******************************************************************************************************************************************
Function    : setDatasetAttributes(tag_t& tDataset,all property values)
Description : Gets the dataset tag and sets attributes like Creation_date/User,last_mod_date/user release date and status 

******************************************************************************************************************************************/
int BW_DocInjector::setDatasetAttributes(tag_t& tDataset,char * cCreatedBy, char * cLastModBy , date_t dtCreationDate , date_t	dtLastModDate, date_t dtRelDate, string sCreationDate, string sModDate, string sRelDate,string sReleaseStatus , int iTCProcessStatus)
{
	int status = ITK_ok;
	
	tag_t tOwner			=	NULLTAG;
	tag_t tModUser			=	NULLTAG;
	tag_t attr_id_dateRel	=	NULLTAG;
	tag_t tRelStatus		=	NULLTAG;

	ITK( AOM_refresh(tDataset, TRUE) );

	ITK( SA_find_user2(cCreatedBy, &tOwner) );
	ITK( SA_find_user2(cLastModBy, &tModUser) );

	logger.write("Setting properties for Dataset ...");
	

	ITK( POM_set_creation_date(tDataset, dtCreationDate) );
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		iTCProcessStatus = 2;
		logger.writebothlog(string("Fail | Creation date Dataset | ") + sCreationDate + " Error code : " + IntToString(status) + " : " + error );
	}
	else
	{
		logger.writeattributelog("Creation date Dataset " ,  sCreationDate );
	}

	

	ITK( POM_set_modification_date(tDataset, dtLastModDate) );
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		iTCProcessStatus = 2;
		logger.writebothlog(string("Fail | Last Modified date Dataset | ") + sModDate + " Error code : " + IntToString(status) + " : " + error );
	}
	else
	{
		logger.writeattributelog("Last Modified date Dataset " ,  sModDate );
	}

	ITK(POM_attr_id_of_attr("date_released", "WorkspaceObject", &attr_id_dateRel));					//Dataset Release Date
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		logger.writebothlog("Error : Getting attribute id of release date : " + IntToString(status) + " : " + error );
		iTCProcessStatus	=	2;
	}
	else
	{
		ITK(POM_set_attr_date(1,&tDataset,attr_id_dateRel, dtRelDate));
		if(status!=ITK_ok)
		{
			char * error = NULL;
			EMH_ask_error_text(status , &error);
			logger.writebothlog("Fail | Release date | " + sRelDate + " : error code : " + IntToString(status) + " : " + error );
			iTCProcessStatus = 2;
		}
		else
		{
			logger.writeattributelog("Release date Dataset" ,  sRelDate);
		}
	}

	int iNDStatuslist = 0;
	tag_t *tNDStatuslist = NULL;
	ITK(WSOM_ask_release_status_list(tDataset,&iNDStatuslist,&tNDStatuslist));
	if(iNDStatuslist == 0)
	{		
		if(tc_strcmp(sReleaseStatus.c_str(),"")!=0)
		{
			ITK(RELSTAT_create_release_status(sReleaseStatus.c_str(),&tRelStatus));
			char* name=NULL;
			AOM_ask_name(tDataset,&name);
			//cout<<"\n dataset name "<<name;
			ITK(RELSTAT_add_release_status(tRelStatus,1,&tDataset,TRUE));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				//cout<<"\n the error " <<error;
				logger.writebothlog("Fail | Release Status Dataset| " + sReleaseStatus + " error code : " + IntToString(status) + " : " + error );
				iTCProcessStatus	=	2;
			}
			else
			{
				logger.writeattributelog("Release Status Dataset" , sReleaseStatus );
			}
		}
	}
					
	ITK( AOM_save(tDataset) );
	ITK( AOM_refresh(tDataset, FALSE) );
	return iTCProcessStatus;
}

/******************************************************************************************************************************************
Function    : setuseranddate(tag_t tItemRev , char * cCreatedBy, char * cLastModBy , date_t dtCreationDate , date_t	dtLastModDate , string sCreationDate, string sModDate , int iTCProcessStatus)
Description : Gets the input tag and sets attributes like Creation_date/User,last_mod_date/user. 

******************************************************************************************************************************************/
int BW_DocInjector::setuseranddate(tag_t tItemRev , char * cCreatedBy, char * cLastModBy , date_t dtCreationDate , date_t	dtLastModDate , string sCreationDate, string sModDate , int iTCProcessStatus)
{
	int status				=	ITK_ok;
	

	char *cObjType				=	NULL;

	tag_t	tOwner			=	NULLTAG;
	tag_t	tModifiedBy		=	NULLTAG;


	POM_set_env_info(POM_bypass_attr_update, FALSE, 0, 0, NULLTAG, NULL);     

	ITK(AOM_ask_value_string(tItemRev,"object_type",&cObjType));

	string sType = cObjType;
	string type = "";
	if(sType.find("Revision")!=std::string::npos)
	{
		type = " For Item Revision";
	}
	else
	{
		type = " For Item";
	}

	
	logger.writeattributelog("Owning User" +  type , "bw_mig" );
	
	AOM_refresh(tItemRev,true);
	
	ITK(POM_set_creation_date(tItemRev, dtCreationDate));
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		logger.writebothlog("Fail | Creation date" + type + " | " + sCreationDate + " error code : " + IntToString(status) + " : " + error );
		iTCProcessStatus	=	2;
	}
	else
	{
		logger.writeattributelog("Creation date" + type, sCreationDate);
	}


	//modification date and user
	ITK(POM_set_modification_date(tItemRev, dtLastModDate));
	if(status!=ITK_ok)
	{
		char * error = NULL;
		EMH_ask_error_text(status , &error);
		logger.writebothlog("Fail : Modification date" + type + " | " + sModDate + " error code : " + IntToString(status) + " : " + error );
		iTCProcessStatus	=	2;
	}
	else
	{
		logger.writeattributelog("Modification date"+type , sModDate );
	}

	logger.writeattributelog("Last Modified User"+type , "bw_mig" );

	if(sType.find("Revision")!=std::string::npos)
	{
		ITEM_save_rev(tItemRev);
	}
	else
	{
		ITEM_save_item(tItemRev);
	}
	AOM_refresh(tItemRev,false);
	
	/*logical isLoaded = false;
	ITK( POM_is_loaded ( tItemRev, &isLoaded));	 
	if ( isLoaded == true )
	{
		ITK( POM_unload_instances ( 1, &tItemRev)); 
	} */
	return iTCProcessStatus;
}

/******************************************************************************************************************************************
Function    : createDataset(tag_t tRev, char* cFileName, char* cFilePath, char* cFileType, tag_t& tDataset , int iTCProcessStatus)
Description : Creates the dataset using Filetype and attach namedreference to it andattach it with corresponding ItemRevision 

******************************************************************************************************************************************/
void BW_DocInjector::createDatasetAndFile(tag_t tRev, char* cFileName, char* cFilePath, char* cFileType, tag_t& tDataset)
{
	int		status			=	ITK_ok;

	tag_t	tDatasetType	=	NULLTAG;
	tag_t	tRelType		=	NULLTAG;
	tag_t	tRelation		=	NULLTAG;
	tag_t	tFileTag		=	NULLTAG;
	
	IMF_file_t 	file_descriptor  = NULL;
	char format_name[AE_io_format_size_c + 1] = "BINARY_REF";

	string	sFileName = cFileName;

	if(sFileName.find(".")!=std::string::npos)
	{
		size_t pos = sFileName.find(".");      // position of "live" in str
		sFileName = sFileName.substr (0,pos);
	}

	string sFileType = TypeToDtsMap(cFileType);
	if(sFileType.length()!=0)
	{
		//check if dataset exist
		ITK(GRM_find_relation_type("IMAN_specification",&tRelType));
		if(status!=ITK_ok)
		{
			char * error = NULL;
			EMH_ask_error_text(status , &error);
			//cout << status << " : "<< error << endl;
		}
		int count = 0;
		tag_t * secondary_objects = NULL;
		GRM_list_secondary_objects_only (tRev,tRelType,&count,&secondary_objects);
		if(status!=ITK_ok)
		{
			char * error = NULL;
			EMH_ask_error_text(status , &error);
			logger.writebothlog("Error while getting secondary objects of item revision: error code : " + IntToString(status) + " : " + error );
		}
	
		boolean bDatasetPresent = false;
		boolean bNamedRefPresent = false;


		for(int inx=0; inx < count; inx++ )
		{
			char * ObjName = NULL;
			ITK( AOM_ask_value_string(secondary_objects[inx], "object_name", &ObjName));
			if(tc_strcmp(ObjName,sFileName.c_str())==0)
			{
				bDatasetPresent = true;
				//dataset present // check for named ref
				int nFound = 0;
				tag_t *referenced_object = NULL;
				ITK(AE_ask_all_dataset_named_refs2	(secondary_objects[inx],cFileName,&nFound,&referenced_object));
				if(nFound!=0)
				{
					//attach named ref
					bNamedRefPresent = true;
					SAFE_MEM_FREE(referenced_object);
				}
				tDataset = secondary_objects[inx];
				break;
			}
		}
		if(secondary_objects!=NULL)
			SAFE_MEM_FREE(secondary_objects);

		if(!bDatasetPresent)
		{
			ITK( AE_find_datasettype2( sFileType.c_str(), &tDatasetType) );
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in finding Dataset Type " + IntToString(status) + " : " + error );

			}
			ITK( AE_create_dataset_with_id(  tDatasetType, cFileName, cFileName, 0, 0, &tDataset) );
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in dataset creation  " + IntToString(status) + " : " + error );

			}

			if(!tc_strcmp( cFileType, "txt" ))
			{
				ITK(AE_set_dataset_format2(tDataset, "TEXT_REF"));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Error in setting dataset format  " + IntToString(status) + " : " + error );

				}
				ITK(AE_import_named_ref(tDataset, TypeToRefMap(cFileType).c_str() ,cFilePath, NULL, SS_TEXT));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Error in importing named reference  " + IntToString(status) + " : " + error );

				}
			}
			else
			{
				ITK(AE_set_dataset_format2(tDataset, format_name));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Error in setting dataset format  " + IntToString(status) + " : " + error );
				}
				ITK(AE_import_named_ref(tDataset,TypeToRefMap(cFileType).c_str() ,cFilePath, NULL, SS_BINARY));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Error in importing named reference  " + IntToString(status) + " : " + error );
				}
			}

			ITK(AOM_save(tDataset));
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in saving dataset  " + IntToString(status) + " : " + error );

			}
	
			ITK( GRM_find_relation_type("IMAN_specification", &tRelType) );
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in finding dataset relation type  " + IntToString(status) + " : " + error );

			}

			ITK( GRM_create_relation( tRev, tDataset, tRelType, NULLTAG, &tRelation) );
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in creating relation  " + IntToString(status) + " : " + error );

			}

			ITK( AOM_save(tRelation) );
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in saving relation  " + IntToString(status) + " : " + error );

			}
			
		}//if dataset not present
		else if(bDatasetPresent && !bNamedRefPresent)
		{
			AOM_refresh(tDataset,true);
			if(!tc_strcmp( cFileType, "txt" ))
			{
				
				ITK(AE_import_named_ref(tDataset, TypeToRefMap(cFileType).c_str() ,cFilePath, NULL, SS_TEXT));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Error in importing named reference  " + IntToString(status) + " : " + error );

				}
			}
			else
			{
				ITK(AE_import_named_ref(tDataset,TypeToRefMap(cFileType).c_str() ,cFilePath, NULL, SS_BINARY));
				if(status!=ITK_ok)
				{
					char * error = NULL;
					EMH_ask_error_text(status , &error);
					logger.writebothlog("Error in importing named reference  " + IntToString(status) + " : " + error );
				}
			}

			ITK(AOM_save(tDataset));
			AOM_refresh(tDataset,false);
			if(status!=ITK_ok)
			{
				char * error = NULL;
				EMH_ask_error_text(status , &error);
				logger.writebothlog("Error in saving dataset  " + IntToString(status) + " : " + error );

			}
		}
	}
	return;
}

/******************************************************************************************************************************************
Function    : getreleasestatus(char * cStatus)
Description : Gets the windchill release state string and returns corresponding Teamcenter release status. 

******************************************************************************************************************************************/
string BW_DocInjector::getreleasestatus(char * cStatus)
{
	string sStatus(cStatus);
	transform(sStatus.begin(), sStatus.end(), sStatus.begin(),(int (*)(int))tolower);

	if(tc_strcmp(sStatus.c_str(),"obsolete") == 0 || tc_strcmp(sStatus.c_str(),"OBSOLETE") == 0 )
	{
		return "Inactive";
	}
	else if(tc_strcmp(sStatus.c_str(),"released") == 0 || tc_strcmp(sStatus.c_str(),"RELEASED") == 0 )
	{
		return "Production";
	}
	else if(tc_strcmp(sStatus.c_str(),"prototype") == 0 || tc_strcmp(sStatus.c_str(),"PROTOTYPE") == 0)
	{
		return "Prototype";
	}
	else
	{
		//contact IT team
		return "";
	}
}

/******************************************************************************************************************************************
Function    : GetcurrentTime()
Description : returns current time in string format

******************************************************************************************************************************************/
string BW_DocInjector::GetcurrentTime()
{
	string sCurrentTime = "";
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%d-%m-%y %H:%M:%S : ",timeinfo);
	//puts (buffer);
	sCurrentTime+=buffer;
	return sCurrentTime;
}

/******************************************************************************************************************************************
Function    : IntToString(int status)
Description : converts integer value to string and returns it

******************************************************************************************************************************************/
string BW_DocInjector::IntToString(int status)
{
	stringstream ss;
	ss << status;
	string str = ss.str();
	return str;
}

/******************************************************************************************************************************************
Function    : monthintostring(char * month)
Description : converts number into corresponding month and return it.

******************************************************************************************************************************************/
string BW_DocInjector::monthintostring(char * month)
{
	if(tc_strcmp(month,"01")==0)
		return "Jan";
	else if(tc_strcmp(month,"02")==0)
		return "Feb";
	else if(tc_strcmp(month,"03")==0)
		return "Mar";
	else if(tc_strcmp(month,"04")==0)
		return "Apr";
	else if(tc_strcmp(month,"05")==0)
		return "May";
	else if(tc_strcmp(month,"06")==0)
		return "Jun";
	else if(tc_strcmp(month,"07")==0)
		return "Jul";
	else if(tc_strcmp(month,"08")==0)
		return "Aug";
	else if(tc_strcmp(month,"09")==0)
		return "Sep";
	else if(tc_strcmp(month,"10")==0)
		return "Oct";
	else if(tc_strcmp(month,"11")==0)
		return "Nov";
	else 
		return "Dec";
	
}
/******************************************************************************************************************************************
Function    : ConvertDate_To_TCFormat(char * cCreationDate)
Description : converts staging DB date format into Teamcenter acceptable format date string

******************************************************************************************************************************************/
string BW_DocInjector::ConvertDate_To_TCFormat(char * cCreationDate)
{
	if(tc_strcmp(cCreationDate,"NULL")==0 || tc_strcmp(cCreationDate,"")==0)
	{
		return "NULL";
	}
	else
	{
		char *	year		=	tc_strtok (cCreationDate, "-");
		char *	month		=	tc_strtok (NULL, "-");
		char *	daytime		=	tc_strtok (NULL, "-");

		char *	day			=	tc_strtok (daytime, " ");
		char *	time		=	tc_strtok (NULL, " ");

		char *  hour		=	tc_strtok (time, ":");
		char *  mins		=	tc_strtok (NULL, ":");


		//cout<< endl << year <<":" << month<< ":" << day << "  " <<hour << "  "<<mins <<endl;
		string month1 =  monthintostring(month);

		string dt = day;
		dt+= "-";
		dt+= month1;dt+= "-";
		dt+= year;dt+=" ";
		dt+=hour;dt+=":";
		dt+=mins;

		return dt;
	}
}


/******************************************************************************************************************************************
Function    : ConvertDate_To_TCFormat(char * cCreationDate)
Description : converts staging DB date format into Teamcenter acceptable format date string

******************************************************************************************************************************************/
string BW_DocInjector::ConvertDate_To_TCFormat_rev(char * cCreationDate,char* cRevID)
{
	if(tc_strcmp(cCreationDate,"NULL")==0 || tc_strcmp(cCreationDate,"")==0)
	{
		return "NULL";
	}
	else
	{
		char *	year		=	tc_strtok (cCreationDate, "-");
		char *	month		=	tc_strtok (NULL, "-");
		char *	daytime		=	tc_strtok (NULL, "-");

		char *	day			=	tc_strtok (daytime, " ");
		char *	time		=	tc_strtok (NULL, " ");

		char *  hour		=	tc_strtok (time, ":");
		char *  mins		=	tc_strtok (NULL, ":");
		char *  sec			=	tc_strtok (NULL, ":");


		//cout<< endl << year <<":" << month<< ":" << day << "  " <<hour << "  "<<mins<<" "<<sec <<endl;
		string month1 =  monthintostring(month);

		string dt = day;
		dt+= "-";
		dt+= month1;dt+= "-";
		dt+= year;dt+=" ";
		dt+=hour;dt+=":";
		dt+=mins;dt+=":";

			int iRev=atoi(cRevID);
		if(iRev <=9)
		{
			dt+="0"+string(cRevID);
		}
		else if(iRev >=59)
		{
		   dt+="59";
		}
		else
		{
		  dt+=string(cRevID);
		}

		
		//dt=dt.substr(0,dt.length()-4);

		return dt;
	}
}

	string BW_DocInjector::getWCUser(char * tcowner)
	{
		string wcuser = "bw_mig";
		string getGroupNUsername = "SELECT [WC_OWNER] FROM [WC2TC_OWNERSHIP] where [TC_OWNER] ='";
		getGroupNUsername+=tcowner; getGroupNUsername+="'";
		vector<string> vOwner = dbObj.executeQuery(getGroupNUsername,2);

		if(vOwner.size()>0)
		{
			string sData = vOwner.at(0);
			cout << sData << endl;

			char * cUserId = tc_strtok ((char *)sData.c_str(), "!");
			
			wcuser			=	cUserId;
		}


		return wcuser;
	}
