function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6463\" class=\"headerLeftMenuInActive\"><a id=\"aID6463\" href=\"#\" OnMouseOver=\"link('_dir','cursor0',this)\" class=\"leftMenuLinkHeadInActive\">cursor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1040\" class=\"leftMenuInActive\"><a id=\"aID1040\" href=\"#\" OnMouseOver=\"link('_class','Cursor49249',this)\" class=\"leftMenuLinkInActive\">Cursor</a></div>\n");
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
