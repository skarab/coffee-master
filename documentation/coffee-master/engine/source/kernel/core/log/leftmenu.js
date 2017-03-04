function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6296\" class=\"headerLeftMenuInActive\"><a id=\"aID6296\" href=\"#\" OnMouseOver=\"link('_dir','log0',this)\" class=\"leftMenuLinkHeadInActive\">log</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID762\" class=\"leftMenuInActive\"><a id=\"aID762\" href=\"#\" OnMouseOver=\"link('_class','Log58373',this)\" class=\"leftMenuLinkInActive\">Log</a></div>\n");
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
