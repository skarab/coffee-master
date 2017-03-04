function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6270\" class=\"headerLeftMenuInActive\"><a id=\"aID6270\" href=\"#\" OnMouseOver=\"link('_dir','prow0',this)\" class=\"leftMenuLinkHeadInActive\">prow</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID730\" class=\"leftMenuInActive\"><a id=\"aID730\" href=\"#\" OnMouseOver=\"link('_class','Prow7127',this)\" class=\"leftMenuLinkInActive\">Prow<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1128\" class=\"leftMenuInActive\"><a id=\"aID1128\" href=\"#\" OnMouseOver=\"link('_member','Prow7578827',this)\" class=\"leftMenuLinkInActive\">Prow</a></div>\n");
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
