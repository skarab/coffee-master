function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6279\" class=\"headerLeftMenuInActive\"><a id=\"aID6279\" href=\"#\" OnMouseOver=\"link('_dir','segment0',this)\" class=\"leftMenuLinkHeadInActive\">segment</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID739\" class=\"leftMenuInActive\"><a id=\"aID739\" href=\"#\" OnMouseOver=\"link('_class','Segment339014',this)\" class=\"leftMenuLinkInActive\">Segment3</a></div>\n");
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
