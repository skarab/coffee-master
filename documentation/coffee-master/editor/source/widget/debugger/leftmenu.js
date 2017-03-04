function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6484\" class=\"headerLeftMenuInActive\"><a id=\"aID6484\" href=\"#\" OnMouseOver=\"link('_dir','debugger0',this)\" class=\"leftMenuLinkHeadInActive\">debugger</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6483\" class=\"leftMenuInActive\"><a id=\"aID6483\" href=\"#\" OnMouseOver=\"link('_dir','pass/pass0',this)\" class=\"leftMenuLinkInActive\">pass</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1094\" class=\"leftMenuInActive\"><a id=\"aID1094\" href=\"#\" OnMouseOver=\"link('_class','Debugger22483',this)\" class=\"leftMenuLinkInActive\">Debugger</a></div>\n");
document.write("<div id=\"divID6183\" class=\"leftMenuInActive\"><a id=\"aID6183\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
