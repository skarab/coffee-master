function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6295\" class=\"headerLeftMenuInActive\"><a id=\"aID6295\" href=\"#\" OnMouseOver=\"link('_dir','error0',this)\" class=\"leftMenuLinkHeadInActive\">error</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID760\" class=\"leftMenuInActive\"><a id=\"aID760\" href=\"#\" OnMouseOver=\"link('_class','Error58373',this)\" class=\"leftMenuLinkInActive\">Error</a></div>\n");
document.write("<div id=\"divID761\" class=\"leftMenuInActive\"><a id=\"aID761\" href=\"#\" OnMouseOver=\"link('_class','ErrorHandler58373',this)\" class=\"leftMenuLinkInActive\">ErrorHandler</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID2367\" class=\"leftMenuInActive\"><a id=\"aID2367\" href=\"#\" OnMouseOver=\"link('_member','Assert774027074',this)\" class=\"leftMenuLinkInActive\">Assert</a></div>\n");
document.write("<div id=\"divID2368\" class=\"leftMenuInActive\"><a id=\"aID2368\" href=\"#\" OnMouseOver=\"link('_member','ERROR_CODE_GetDescription1978402964',this)\" class=\"leftMenuLinkInActive\">ERROR_CODE_GetDescription</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6211\" class=\"leftMenuInActive\"><a id=\"aID6211\" href=\"#\" OnMouseOver=\"link('_member','ERROR_CODE6535345',this)\" class=\"leftMenuLinkInActive\">ERROR_CODE</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
