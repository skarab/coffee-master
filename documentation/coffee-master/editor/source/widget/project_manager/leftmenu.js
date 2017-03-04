function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6495\" class=\"headerLeftMenuInActive\"><a id=\"aID6495\" href=\"#\" OnMouseOver=\"link('_dir','project_manager0',this)\" class=\"leftMenuLinkHeadInActive\">project_manager</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6494\" class=\"leftMenuInActive\"><a id=\"aID6494\" href=\"#\" OnMouseOver=\"link('_dir','deploy/deploy0',this)\" class=\"leftMenuLinkInActive\">deploy</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6203\" class=\"leftMenuInActive\"><a id=\"aID6203\" href=\"#\" OnMouseOver=\"link('_class','Dialog0',this)\" class=\"leftMenuLinkInActive\">Dialog</a></div>\n");
document.write("<div id=\"divID1109\" class=\"leftMenuInActive\"><a id=\"aID1109\" href=\"#\" OnMouseOver=\"link('_class','ProjectGeneral22483',this)\" class=\"leftMenuLinkInActive\">ProjectGeneral</a></div>\n");
document.write("<div id=\"divID1110\" class=\"leftMenuInActive\"><a id=\"aID1110\" href=\"#\" OnMouseOver=\"link('_class','ProjectManager22483',this)\" class=\"leftMenuLinkInActive\">ProjectManager</a></div>\n");
document.write("<div id=\"divID1111\" class=\"leftMenuInActive\"><a id=\"aID1111\" href=\"#\" OnMouseOver=\"link('_class','ProjectPlugins22483',this)\" class=\"leftMenuLinkInActive\">ProjectPlugins</a></div>\n");
document.write("<div id=\"divID6180\" class=\"leftMenuInActive\"><a id=\"aID6180\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
