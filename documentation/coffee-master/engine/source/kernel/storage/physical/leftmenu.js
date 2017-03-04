function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6336\" class=\"headerLeftMenuInActive\"><a id=\"aID6336\" href=\"#\" OnMouseOver=\"link('_dir','physical0',this)\" class=\"leftMenuLinkHeadInActive\">physical</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID837\" class=\"leftMenuInActive\"><a id=\"aID837\" href=\"#\" OnMouseOver=\"link('_class','PhysicalPath35340',this)\" class=\"leftMenuLinkInActive\">PhysicalPath</a></div>\n");
document.write("<div id=\"divID838\" class=\"leftMenuInActive\"><a id=\"aID838\" href=\"#\" OnMouseOver=\"link('_class','PhysicalSystem35340',this)\" class=\"leftMenuLinkInActive\">PhysicalSystem</a></div>\n");
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
