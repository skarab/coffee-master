function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6453\" class=\"headerLeftMenuInActive\"><a id=\"aID6453\" href=\"#\" OnMouseOver=\"link('_dir','progress_bar0',this)\" class=\"leftMenuLinkHeadInActive\">progress_bar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1028\" class=\"leftMenuInActive\"><a id=\"aID1028\" href=\"#\" OnMouseOver=\"link('_class','ProgressBar45101',this)\" class=\"leftMenuLinkInActive\">ProgressBar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6247\" class=\"leftMenuInActive\"><a id=\"aID6247\" href=\"#\" OnMouseOver=\"link('_member','PROGRESS_BAR_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">PROGRESS_BAR_STYLE</a></div>\n");
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
