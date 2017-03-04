function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6286\" class=\"headerLeftMenuInActive\"><a id=\"aID6286\" href=\"#\" OnMouseOver=\"link('_dir','matrix0',this)\" class=\"leftMenuLinkHeadInActive\">matrix</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID745\" class=\"leftMenuInActive\"><a id=\"aID745\" href=\"#\" OnMouseOver=\"link('_class','Matrix39014',this)\" class=\"leftMenuLinkInActive\">Matrix</a></div>\n");
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
