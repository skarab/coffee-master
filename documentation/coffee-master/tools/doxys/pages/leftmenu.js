function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6262\" class=\"headerLeftMenuInActive\"><a id=\"aID6262\" href=\"#\" OnMouseOver=\"link('_dir','pages0',this)\" class=\"leftMenuLinkHeadInActive\">pages</a></div>\n");
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
