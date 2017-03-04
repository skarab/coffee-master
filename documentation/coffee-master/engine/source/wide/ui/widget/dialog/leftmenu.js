function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6446\" class=\"headerLeftMenuInActive\"><a id=\"aID6446\" href=\"#\" OnMouseOver=\"link('_dir','dialog0',this)\" class=\"leftMenuLinkHeadInActive\">dialog</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1020\" class=\"leftMenuInActive\"><a id=\"aID1020\" href=\"#\" OnMouseOver=\"link('_class','Dialog45101',this)\" class=\"leftMenuLinkInActive\">Dialog</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6241\" class=\"leftMenuInActive\"><a id=\"aID6241\" href=\"#\" OnMouseOver=\"link('_member','DIALOG_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">DIALOG_STYLE</a></div>\n");
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
