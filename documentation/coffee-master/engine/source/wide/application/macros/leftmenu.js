function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6414\" class=\"headerLeftMenuInActive\"><a id=\"aID6414\" href=\"#\" OnMouseOver=\"link('_dir','macros0',this)\" class=\"leftMenuLinkHeadInActive\">macros</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID683\" class=\"leftMenuInActive\"><a id=\"aID683\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_RegisterApplication948934486',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('COFFEE_RegisterApplication');\" onmouseout=\"return nd();\">COFFEE_RegisterApplicatio.<img src=\"../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
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
