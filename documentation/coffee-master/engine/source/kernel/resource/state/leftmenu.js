function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6324\" class=\"headerLeftMenuInActive\"><a id=\"aID6324\" href=\"#\" OnMouseOver=\"link('_dir','state0',this)\" class=\"leftMenuLinkHeadInActive\">state</a></div>\n");
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
