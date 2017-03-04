function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6487\" class=\"headerLeftMenuInActive\"><a id=\"aID6487\" href=\"#\" OnMouseOver=\"link('_dir','explorer0',this)\" class=\"leftMenuLinkHeadInActive\">explorer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6486\" class=\"leftMenuInActive\"><a id=\"aID6486\" href=\"#\" OnMouseOver=\"link('_dir','path_info/path_info0',this)\" class=\"leftMenuLinkInActive\">path_info</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1097\" class=\"leftMenuInActive\"><a id=\"aID1097\" href=\"#\" OnMouseOver=\"link('_class','Explorer22483',this)\" class=\"leftMenuLinkInActive\">Explorer</a></div>\n");
document.write("<div id=\"divID6174\" class=\"leftMenuInActive\"><a id=\"aID6174\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
