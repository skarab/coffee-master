function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6511\" class=\"headerLeftMenuInActive\"><a id=\"aID6511\" href=\"#\" OnMouseOver=\"link('_dir','macros0',this)\" class=\"leftMenuLinkHeadInActive\">macros</a></div>\n");
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
